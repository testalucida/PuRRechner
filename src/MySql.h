/*
 * MySql.h
 *
 *  Created on: 17.06.2012
 *      Author: max
 */

#ifndef MYSQL_H_
#define MYSQL_H_

#include <my/ColumnInfo.h>

#include <string>
#include <mysql.h>
#include <cstdio>
#include <exception>

using namespace std;

namespace my {
    class TableData;
}

class MySqlException: public std::exception {
public:
	MySqlException( int err, const string &msg ) throw() :
		_errno(err)
	{
		char buf[15];
		sprintf( buf, "%d", err );
		_msg.append( "Error " );
		_msg.append( buf );
		_msg.append( ": " );
		_msg.append( msg );
	}

	virtual ~MySqlException() throw() {
	}

	/** Returns a C-style character string describing the general cause
	 *  of the current error.  */
	virtual const char* what() const throw() {
		return _msg.c_str();
	}
private:
	int _errno;
	std::string _msg;
};

struct TypeConversion {
    int mysql_type;
    int db2_type;
};

static const TypeConversion typeConversions[] = {
  {MYSQL_TYPE_DECIMAL, my::TYPE_DECIMAL}
, {MYSQL_TYPE_TINY, my::TYPE_SHORT}
, {MYSQL_TYPE_SHORT, my::TYPE_SHORT }
, {MYSQL_TYPE_LONG, my::TYPE_INT}
, {MYSQL_TYPE_FLOAT, my::TYPE_FLOAT}
, {MYSQL_TYPE_DOUBLE, my::TYPE_DOUBLE}
, {MYSQL_TYPE_NULL, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_TIMESTAMP, my::TYPE_TIMESTAMP}
, {MYSQL_TYPE_LONGLONG, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_INT24, my::TYPE_INT}
, {MYSQL_TYPE_DATE, my::TYPE_DATE  }
, {MYSQL_TYPE_TIME, my::TYPE_TIME}
, {MYSQL_TYPE_DATETIME, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_YEAR, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_NEWDATE, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_VARCHAR, my::TYPE_VARCHAR}
, {MYSQL_TYPE_BIT, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_NEWDECIMAL, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_ENUM, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_SET, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_TINY_BLOB, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_MEDIUM_BLOB, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_LONG_BLOB, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_BLOB, my::TYPE_UNKNOWN}
, {MYSQL_TYPE_VAR_STRING, my::TYPE_NTS}
, {MYSQL_TYPE_STRING, my::TYPE_NTS}
, {MYSQL_TYPE_GEOMETRY, my::TYPE_UNKNOWN}
};

/**
 *
 */
class MySql {
public:
//	MySql();
	void connect( const char *user, const char *db, const char *passwd = NULL,
			const char *host = "localhost" );

//	void select( const char* sql );
    void select( const char *pSql, my::TableData &data );
	void startTransaction();
	int exec( const char* sql );
	void commit();
	void rollback();
//	int getColumnCount() const;
//	const ColumnInfo& getColumnInfo( int colIdx ) const;
	const char* getErrorMessage() const;
	void disconnect();
	virtual ~MySql();
private:
	void throwEx( int err, const char *msg = NULL );
    void fetch( my::TableData &data );
    my::DataType convertType( enum_field_types mysqlType ) const;
private:
	MYSQL *_mysql;
	MYSQL_RES *_res;
	int _fieldCount;
//	ColumnInfo *_pColInfos;
	std::string _errorMsg;
};

//} /* namespace my */
#endif /* MYSQL_H_ */
