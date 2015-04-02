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
                , JhrlEtragNachSteuern( 0 )
    {}
    int AnzahlAktiveVertraege;
    int SummeInvest;
    int DepotwertHeute;
    int SummeRueckkaufwerte;
    int SummeVeraeussGewinne;
    int JhrlEtragNachSteuern;
};

class DepotDataCalculator {
public:
    DepotDataCalculator( VertragPtrVectorPtr pVertraegeVector );
    DepotData getDepotData() const;
    int getJahresErtragNachSteuern( float steuersatz ) const;
    virtual ~DepotDataCalculator();
private:
    float getVertragsrestwert( VertragPtr pVertrag ) const;
    int getJahresmiete( VertragPtr pV ) const;
    /**
     * errechnet die Anzahl der Miettage im aktuellen Jahr.
     */
    int getMiettage( const my::MyDate &mietBeginn, 
                     const my::MyDate &mietEnde ) const;
private:
    VertragPtrVectorPtr _pVertraegeVector;
};

#endif	/* DEPOTWERT_H */

