/* 
 * File:   DepotWert.h
 * Author: max
 *
 * Created on 13. Februar 2015, 23:04
 */

#ifndef DEPOTWERT_H
#define	DEPOTWERT_H

#include "Vertrag.h"

struct DepotData {
    DepotData() : AnzahlAktiveVertraege(0)
                , SummeInvest( 0 )
                , DepotwertHeute(0)
                , SummeRueckkaufwerte(0)
                , SummeVeraeussGewinne( 0 )
                , Jahresmiete( 0 )
                , JahresertragVorSteuer( 0 )
    {}
    int AnzahlAktiveVertraege;
    int SummeInvest;
    int DepotwertHeute;
    int SummeRueckkaufwerte;
    int SummeVeraeussGewinne;
    int Jahresmiete;
    int JahresertragVorSteuer; //Einnahmen - Wertverlust
};

class DepotDataCalculator {
public:
    DepotDataCalculator( VertragPtrVectorPtr pVertraegeVector );
    DepotData getDepotData() const;
    
    /**
     * Ermittelt den jährlichen Ertrag eines Vertrags vor Steuern.
     * Der Ertrag eines Containers errechnet sich aus 
     * Tagesmiete * Anzahl Miettage im Jahr (=Einnahmen) MINUS
     *  ((Einzelpreis - Rückkauf) / Jahre Laufzeit) (=Wertverlust).
     * Für einen Vertrag entsprechend multipliziert mit der Anzahl Container.
     * @return Eurobetrag
     */
    int getJahresertragVorSteuern( VertragPtr pVertrag ) const;
    
    virtual ~DepotDataCalculator();
private:
    float getVertragsrestwert( VertragPtr pVertrag ) const;
    
    /**
     * Errechnet die Jahresmiete für den Vertrag pV 
     * im aktuellen Jahr.
     * Maßgeblich sind die im Vertrag angegebene Tagesmiete
     * und die Anzahl der Tage, die der Vertrag im 
     * aktuellen Jahr aktiv war.
     * NB: die Tagesmiete enthält auch den AfA-Anteil.
     * @param pV der Vertrag, dessen Miete berechnet werden soll.
     * @return die Miete im aktuellen Jahr
     */
//    int getJahresmiete( VertragPtr pV ) const;
    
    /**
     * errechnet die Anzahl der Miettage im aktuellen Jahr.
     */
    int getMiettage( const my::MyDate &mietBeginn, 
                     const my::MyDate &mietEnde ) const;
private:
    VertragPtrVectorPtr _pVertraegeVector;
};

#endif	/* DEPOTWERT_H */

