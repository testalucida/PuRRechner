/* 
 * File:   DepotWert.cpp
 * Author: max
 * 
 * Created on 13. Februar 2015, 23:04
 */

#include "DepotWertCalculator.h"
#include "ContainerIO.h"
#include <algorithm>

DepotWertCalculator::DepotWertCalculator( ) {
}

DepotWert DepotWertCalculator::getDepotWert() const {
    ContainerIO io;
    io.connect();
    WertverlustVectorPtr pWvVector = io.getWertverluste();
    
    DepotWert depotWert;
    std::for_each( pWvVector->begin(), pWvVector->end(), [&depotWert] (WertverlustDataPtr pWv ) {
        depotWert.SummeRueckkaufwerte += pWv->Rueckkauf;
        float wertverlust = pWv->WertverlustProTag * pWv->TageRestlaufzeit;
        int restwert = pWv->Rueckkauf + wertverlust;
        depotWert.DepotwertHeute += restwert;
    } );
    
    return depotWert;
}

DepotWertCalculator::~DepotWertCalculator( ) {
}

