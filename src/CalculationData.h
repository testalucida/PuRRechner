/* 
 * File:   CalculationData.h
 * Author: max
 *
 * Created on 6. Februar 2015, 16:48
 */

#ifndef CALCULATIONDATA_H
#define	CALCULATIONDATA_H

/**
 Kalkulationsdaten bezogen auf 1 Container
 */
struct CalculationData {
public:
    float Einzelpreis;
    float MieteProTag;
    int JahreLaufzeit;
    float Rueckkaufpreis;
    float AfA;
    float Steuersatz;
};


#endif	/* CALCULATIONDATA_H */

