/* 
 * File:   DepotWert.cpp
 * Author: max
 * 
 * Created on 13. Februar 2015, 23:04
 */

#include "DepotDataCalculator.h"
#include "ContainerIO.h"

#include <my/datetimecalculator.h>

#include <algorithm>

DepotDataCalculator::DepotDataCalculator( VertragPtrVectorPtr pVertraegeVector ) 
: _pVertraegeVector( pVertraegeVector )
{
}

DepotData DepotDataCalculator::getDepotData() const {
    DepotData depotData;
    MyDate today( true );
    
    for_each( _pVertraegeVector->begin(), _pVertraegeVector->end(), [&] (VertragPtr pV ) {
        //Nur aktive Verträge berücksichtigen:
        if( pV->Mietende > today ) {
            //der heutige Depotwert ergibt sich aus der Summierung der einzelnen
            //Vertrags-Restwerte
            depotData.DepotwertHeute += getVertragsrestwert( pV );
      
            //Rückkaufswerte aufsummieren:
            depotData.SummeRueckkaufwerte += ( pV->Rueckkaufswert * pV->Menge );
            depotData.AnzahlAktiveVertraege++;
            
            //Veräußerungsgewinne aufsummieren.
            depotData.SummeVeraeussGewinne += pV->Veraeusserungsgewinn;;
        }
        
    } );
    
    return depotData;
}

float DepotDataCalculator::getVertragsrestwert( VertragPtr pV ) const {
    /////////Zeitwert des Vertrags ausrechnen. ////////////////
    //  a) Wertverlust pro Tag EINES Containers nach der Formel:
    //     ((einzelpreis - rueckkauf) * menge) / (jahremietdauer*365)
    float wertverlustProTag = ((pV->Einzelpreis - pV->Rueckkaufswert) ) /
                              (pV->JahreMietdauer * 365 );
    //  b) Tage Restlaufzeit:
    MyDate today( true );
    int tageRestlaufzeit = 
        my::DateTimeCalculator::GetDuration( today, pV->Mietende );

    //  c) Wertverlust von heute bis zum Schluss: 
    float wertverlust = tageRestlaufzeit * wertverlustProTag;

    //  d) der derzeitige Restwert errechnet sich aus dem Rückkaufswert 
    //     PLUS dem noch kommenden wertverlust
    float restwert = pV->Rueckkaufswert + wertverlust;
    
    return restwert * pV->Menge;
}

DepotDataCalculator::~DepotDataCalculator( ) {
}

