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
    {}
    int AnzahlAktiveVertraege;
    int SummeInvest;
    int DepotwertHeute;
    int SummeRueckkaufwerte;
    int SummeVeraeussGewinne;
};

class DepotDataCalculator {
public:
    DepotDataCalculator( VertragPtrVectorPtr pVertraegeVector );
    DepotData getDepotData() const;
    virtual ~DepotDataCalculator();
private:
    float getVertragsrestwert( VertragPtr pVertrag ) const;
private:
    VertragPtrVectorPtr _pVertraegeVector;
};

#endif	/* DEPOTWERT_H */

