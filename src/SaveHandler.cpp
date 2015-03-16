/* 
 * File:   SaveHandler.cpp
 * Author: max
 * 
 * Created on 9. Februar 2015, 21:54
 */

#include "SaveHandler.h"
#include "ContainerIO.h"
#include "MainWindow.h"
#include "Vertrag.h"
#include "Vertraege.h"

SaveHandler::SaveHandler( ) : _pVertraege( NULL ) {
}

void SaveHandler::setVertraege( VertraegeTableData &vertraege ) {
    _pVertraege = &vertraege;
}

void SaveHandler::saveVertrag( MainWindow &w, Vertrag &v ) {
    ContainerIO io;
    io.connect();
    
    VertragPtr pVertrag = io.selectVertrag( v.Vertrag.get(), v.LfdNr );
    
    if( pVertrag->isEmpty() ) {
        io.insertVertrag( v );
        //TODO: muss der neue Vertrag in _pVertraege aufgenommen werden?
        //Wenn nicht hier, wer macht das dann wo?
    } else {
        io.updateVertrag( v );
    }
    
    //w.clear();
    
    if( _pVertraege ) {
        _pVertraege->clear();
        io.getVertraege( *_pVertraege );
    }
    
}
 
SaveHandler::~SaveHandler( ) { 
    
}

