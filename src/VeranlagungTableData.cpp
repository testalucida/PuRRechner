/* 
 * File:   Veranlagungsdaten.cpp
 * Author: max
 * 
 * Created on 15. März 2015, 10:38
 */

#include "VeranlagungTableData.h"

using namespace my;

VeranlagungTableData::VeranlagungTableData( ) {
    for( const char **ppNames = VeranlagungsdatenHeaderNames; *ppNames; ppNames++ ) {
        this->addColumn( *ppNames );
    }
}

void VeranlagungTableData::
     setValue( const char *pVal, int row, const char *pColumnName ) 
{
    int col = getColumnIndex( pColumnName );
    TableData::setValue( pVal, row, col );
}

VeranlagungTableData::~VeranlagungTableData( ) {
}

