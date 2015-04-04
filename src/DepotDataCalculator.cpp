/* 
 * File:   DepotWert.cpp
 * Author: max
 * 
 * Created on 13. Februar 2015, 23:04
 */

#include "DepotDataCalculator.h"
#include "ContainerIO.h"
#include "VeranlagungCalculator.h"

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
        //Nur Verträge berücksichtigen, die wenigstens 1 Tag Miete in diesem Jahr
        //erbracht haben:
        int miettage = getMiettage( pV->Mietbeginn, pV->Mietende );
        if( miettage > 0 ) {
            //Ankäufe summieren:
            depotData.SummeInvest += pV->Gesamtpreis;
            
            if( pV->Mietende > today ) {
                //der heutige Depotwert ergibt sich aus der Summierung der einzelnen
                //Vertrags-Restwerte von Verträgen, die noch aktiv sind
                depotData.DepotwertHeute += getVertragsrestwert( pV );

                //Rückkaufswerte aufsummieren:
                depotData.SummeRueckkaufwerte += ( pV->Rueckkaufswert * pV->Menge );
                depotData.AnzahlAktiveVertraege++;
            }
            
            //Veräußerungsgewinne aufsummieren.
            depotData.SummeVeraeussGewinne += pV->Veraeusserungsgewinn;
            
            //Mietertrag über alle Verträge/Container aufsummieren.
            depotData.Jahresmiete += ( miettage * pV->Tagesmiete * pV->Menge );
            
            //Mietertrag vor Steuern aufsummieren:
            depotData.JahresertragVorSteuer += getJahresertragVorSteuern( pV );
        }
    } );
    
    return depotData;
}

int DepotDataCalculator::getJahresertragVorSteuern( VertragPtr pV ) const {
    int ertrag = 0;

    int miettage = getMiettage( pV->Mietbeginn, pV->Mietende );

    if( miettage > 0 ) {
        int einnahmen = pV->Tagesmiete * miettage;
        int wertverlust = (pV->Einzelpreis - pV->Rueckkaufswert) / pV->JahreMietdauer;
        ertrag += ( ( einnahmen - wertverlust ) * pV->Menge );
    }
    
    fprintf( stderr, "Vertrag %s, Beginn %s, Ende %s, Miettage: %d, Ertrag: %d\n", 
            pV->Vertrag.get(), 
            pV->Mietbeginn.ToEurString().c_str(), 
            pV->Mietende.ToEurString().c_str(),
            miettage, ertrag );
    
    return ertrag;
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

//int DepotDataCalculator::getJahresmiete( VertragPtr pV ) const {
//    
//    int miettage = getMiettage( pV->Mietbeginn, pV->Mietende );
//    return miettage * pV->Tagesmiete * pV->Menge;
//}

int DepotDataCalculator::getMiettage( const my::MyDate &mietBeginn, 
                                      const my::MyDate &mietEnde ) const 
{
    MyDate today( true );
    VeranlagungCalculator calc;
    return calc.getAnzahlMiettage( mietBeginn, mietEnde, today.GetYear() );
}

DepotDataCalculator::~DepotDataCalculator( ) {
}

