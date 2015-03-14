/* 
 * File:   Vertraege.cpp
 * Author: max
 * 
 * Created on 18. April 2014, 22:08
 */

#include "Vertraege.h"



using namespace my;


VertraegeTableData::VertraegeTableData( ) : TableData() {
    
}

VertragPtrVectorPtr VertraegeTableData::getVertraege() {
    buildHeaderIndexMapper();
    
    VertragPtrVectorPtr pVertragPtrVector( new std::vector<VertragPtr>() );
    
    for( int r = 0, rmax = getRowCount(); r < rmax; r++ ) {
        VertragPtr pV = createVertragFromRow( r );
        pVertragPtrVector->push_back( pV );
    }
    
    return pVertragPtrVector;
}

VertragPtr VertraegeTableData::getVertrag( int idx ) const {
    return createVertragFromRow( idx );
}

void VertraegeTableData::buildHeaderIndexMapper() {
    for( int c = 0, cmax = this->getColumnCount(); c < cmax; c++ ) {
        const char *pHeader = getColumnHeader( c );
        _headerIndexMapper.insert( pair<string, int>( pHeader, c ) );
    }
}

VertragPtr VertraegeTableData::createVertragFromRow( int row ) const {
    VertragPtr pV( new Vertrag() );
    pV->AfA = getFloatValue( row, getColumnIndex("afa") );
    pV->Angebot.add( getValue( row, getColumnIndex( "angebot" ) ) );
    pV->Einzelpreis = getFloatValue( row, getColumnIndex( "einzelpreis" ) );
    pV->Gesamtpreis = getFloatValue( row, getColumnIndex( "gesamtpreis" ) );
    pV->JahreMietdauer = getIntValue( row, getColumnIndex( "jahremietdauer" ) );
    pV->Kunde.add( getValue( row, getColumnIndex( "kunde" ) ) );
    pV->LfdNr = getIntValue( row, getColumnIndex( "lfdnr" ) );
    pV->Menge = getIntValue( row, getColumnIndex( "menge") );
    pV->Mietbeginn = getDateValue( row, getColumnIndex( "mietbeginn") );
    pV->Mietende = getDateValue( row, getColumnIndex( "mietende") );
    pV->Rueckkaufswert = getFloatValue( row, getColumnIndex( "rueckkauf" ) );
    pV->Tagesmiete = getFloatValue( row, getColumnIndex( "tagesmiete" ) );
    pV->Veraeusserungsgewinn = getFloatValue( row, getColumnIndex( "veraeussgewinn" ) );
    pV->Vertrag.add( getValue( row, getColumnIndex( "vertrag" ) ) );
    return pV;
}

int VertraegeTableData::getColumnIndex( const char *pHeader ) const {
    int idx = _headerIndexMapper.at( pHeader );
    return idx;
}

VertraegeTableData::~VertraegeTableData( ) {
}

