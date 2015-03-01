/*
 * MySql.cpp
 *
 *  Created on: 17.06.2012
 *      Author: max
 */

#include "MySql.h"

#include <my/TableData.h>

#include <cstdio>
#include <cstring>

using namespace my;
//namespace my {

//MySql::MySql() : _pColInfos( NULL ) {
//}

void MySql::connect( const char* user,
					const char* db,
					const char* passwd,
					const char* host )
{
	_mysql = mysql_init( NULL );

	if( ! _mysql ) {
		throwEx( -1 );
	}

	mysql_real_connect( _mysql, host,
				user, passwd, db, 0, NULL, 0 );
	int rc = mysql_errno( _mysql );
	if( rc != 0 ) {
		throwEx( rc );
	}
}

void MySql::throwEx( int err, const char *msg ) {
	if( msg ) {
		_errorMsg = msg;
	} else {
		_errorMsg = mysql_error( _mysql );
	}
	_res = NULL;
	MySqlException ex( err, _errorMsg );
	throw( ex );
}

//void MySql::select( const char* sql ) {
//	int errno = mysql_query( _mysql, sql );
//	if( errno != 0 ) {
//		throwEx( errno );
//	} else {
//		_res = mysql_store_result( _mysql );
//		_fieldCount = mysql_num_fields( _res );
//		MYSQL_FIELD *field = mysql_fetch_field( _res );
//		if( _pColInfos ) {
//			delete[] _pColInfos;
//			_pColInfos = NULL;
//		}
//		_pColInfos = new ColumnInfo[_fieldCount];
//		for( int i = 0; i < _fieldCount; i++ ) {
//			_pColInfos[i].name = field[i].name;
//			_pColInfos[i].length = field[i].length;
//			_pColInfos[i].maxLength = field[i].max_length;
//			_pColInfos[i].type = field[i].type;
//		}
//	}
//}

void MySql::select( const char* sql, TableData &data ) {
	int err = mysql_query( _mysql, sql );
	if( err != 0 ) {
		throwEx( err );
	} else {
		_res = mysql_store_result( _mysql );
        if( !_res ) return;
        
		_fieldCount = mysql_num_fields( _res );
		MYSQL_FIELD *field = mysql_fetch_field( _res );

		for( int i = 0; i < _fieldCount; i++ ) {
            ColumnInfo ci( i, field[i].name, 
                           convertType( field[i].type ),                           
                           field[i].length, 
                           (short)field[i].decimals,
                           true /*is null -- unknown to mysql*/ );
            data.addColumn( ci );
		}
        fetch( data );
	}
}

DataType MySql::convertType( enum_field_types mysqlType ) const {
    for( int t = 0; t <= MYSQL_TYPE_GEOMETRY; t++ ) {
        if( typeConversions[t].mysql_type == mysqlType ) {
            return (DataType)typeConversions[t].db2_type;
        }
    }
    return TYPE_UNKNOWN;
}

void MySql::fetch( my::TableData &data ) {
	MYSQL_ROW row = mysql_fetch_row( _res );
	if( ! row ) {
		mysql_free_result( _res );
		_res = NULL;
        return;
	}
    
    do {
        int r = data.addRow();
        for( int c = 0; c < _fieldCount; c++ ) {
            data.setValue( row[c], r, c );
        }
    } while( ( row = mysql_fetch_row( _res ) ) );
}

int MySql::exec( const char* sql ) {
	int err = mysql_query( _mysql, sql );
	if( err != 0 ) {
		throwEx( err );
	}
	return mysql_affected_rows( _mysql );
}

void MySql::startTransaction() {
	if( mysql_autocommit( _mysql, 0 ) != 0 ) {
		_errorMsg = mysql_error( _mysql );
		throwEx( -1, "MySql::startTransaction() not successful" );
	}
}

void MySql::commit() {
	if( mysql_commit( _mysql ) != 0 ) {
		_errorMsg = mysql_error( _mysql );
		throwEx( -1, "MySql::commit() failed" );
	}
	mysql_autocommit( _mysql, true );
}

void MySql::rollback() {
	if( mysql_rollback( _mysql ) != 0 ) {
		_errorMsg = mysql_error( _mysql );
		throwEx( -1, "MySql::rollback() failed" );
	}
	mysql_autocommit( _mysql, true );
}

const char* MySql::getErrorMessage() const {
	return _errorMsg.c_str();
}

void MySql::disconnect() {
	mysql_close( _mysql );
}

//int MySql::getColumnCount() const {
//	return _fieldCount;
//}

//const ColumnInfo& MySql::getColumnInfo( int colIdx ) const {
//	return _pColInfos[colIdx];
//}

MySql::~MySql() {
//	if( _pColInfos ) {
//		delete[] _pColInfos;
//	}
}

//} /* namespace my */
