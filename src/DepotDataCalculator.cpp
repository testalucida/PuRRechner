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
            //Ankäufe summieren:
            depotData.SummeInvest += pV->Gesamtpreis;
            
            //der heutige Depotwert ergibt sich aus der Summierung der einzelnen
            //Vertrags-Restwerte
            depotData.DepotwertHeute += getVertragsrestwert( pV );
      
            //Rückkaufswerte aufsummieren:
            depotData.SummeRueckkaufwerte += ( pV->Rueckkaufswert * pV->Menge );
            depotData.AnzahlAktiveVertraege++;
            
            //Veräußerungsgewinne aufsummieren.
            depotData.SummeVeraeussGewinne += pV->Veraeusserungsgewinn;
            
            //Mietertrag über alle Verträge/Container aufsummieren.
            depotData.JhrlEtragNachSteuern += getJahresmiete( pV );
        }
        
    } );
    
    return depotData;
}

int DepotDataCalculator::getJahresErtragNachSteuern( float steuersatz ) const{
    return 12345;
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

int DepotDataCalculator::getJahresmiete( VertragPtr pV ) const {
    int miettage = getMiettage( pV->Mietbeginn, pV->Mietende );
    return miettage * pV->Tagesmiete * pV->Menge;
}

int DepotDataCalculator::getMiettage( const my::MyDate &mietBeginn, 
                                      const my::MyDate &mietEnde ) const 
{
    MyDate today( true );
    MyDate first = mietBeginn < today ? mietBeginn : today;
    MyDate last = mietEnde > today ? mietEnde : today;
    
    int miettage = DateTimeCalculator::GetDuration( first, last );
    return miettage;
}

DepotDataCalculator::~DepotDataCalculator( ) {
}

