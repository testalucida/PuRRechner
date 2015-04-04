/* 
 * File:   VertragProvider.cpp
 * Author: max
 * 
 * Created on 4. April 2015, 19:47
 */

#include "VertragProvider.h"
#include "Vertraege.h"

VertragProvider *VertragProvider::_pThis = NULL;

VertragProvider &VertragProvider::instance() {
    if( _pThis == NULL ) {
        _pThis = new VertragProvider();
        atexit( destroy );
    }
    return *_pThis;
}

VertraegeTableData &VertragProvider::getVertraege( VertraegeTableData &vertraege ) {
    _containerIO.getVertraege( vertraege );
    
    //Für jeden Vertrag den Veräußerungsgewinn berechnen:
    //menge * (rueckkauf - ((einzelpreis*afa*jahremietdauer)/100))
    //Für Verträge, die vor dem 1.1.2009 abgeschlossen wurden, fällt kein
    //Veräußerungsgewinn an.
    MyDate stichtag( 1, 1, 2009 );
    int gewinnIdx = vertraege.getColumnIndex( "veraeussgewinn" );
    for( int r = 0, rmax = vertraege.getRowCount(); r < rmax; r++ ) {
        VertragPtr pV = vertraege.getVertrag( r );
        if( pV->Mietbeginn < stichtag ) {
            pV->Veraeusserungsgewinn = 0;
        } else {
            float gesamtAfA = ( pV->Einzelpreis * pV->AfA * pV->JahreMietdauer ) / 100;
            float restwert = pV->Einzelpreis - gesamtAfA;
            int gewinn = (pV->Rueckkaufswert - restwert) * pV->Menge;
            
            vertraege.setValue( gewinn, r, gewinnIdx );
        }
    }
    
    return vertraege;
}

VertragProvider::VertragProvider( ) {
    _containerIO.connect();
}

void VertragProvider::destroy() {
    delete _pThis;
}

VertragProvider::~VertragProvider( ) {
   
}

