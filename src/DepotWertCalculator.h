/* 
 * File:   DepotWert.h
 * Author: max
 *
 * Created on 13. Februar 2015, 23:04
 */

#ifndef DEPOTWERT_H
#define	DEPOTWERT_H

struct DepotWert {
    int DepotwertHeute;
    int SummeRueckkaufwerte;
};

class DepotWertCalculator {
public:
    DepotWertCalculator();
    DepotWert getDepotWert() const;
    virtual ~DepotWertCalculator();
private:

};

#endif	/* DEPOTWERT_H */

