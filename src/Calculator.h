/* 
 * File:   Calculator.h
 * Author: max
 *
 * Created on 7. Februar 2015, 16:08
 */

#ifndef CALCULATOR_H
#define	CALCULATOR_H

#include "MainWindow.h"


class Calculator {
public:
    Calculator();
    void onCalculate( IRendite &rendite, CalculationData &data );
    virtual ~Calculator();
    
    /**
     * Kalkuliert die Rendite für 1 Container ohne Berücksichtigung
     * der AfA
     * @param  data: Daten für 1 Container
     * @return 
     */
    float calculateOhneAfa( const CalculationData & ) const;
    
    /**
     * Kalkuliert die Rendite für 1 Container unter Berücksichtigung
     * der AfA
     * @param  data: Daten für 1 Container
     * @return 
     */
    float calculateMitAfa( const CalculationData & ) const;
    
    /**
     * Errechnet den Diskontierungssummenfaktor
     * @param zins: in Prozent, z.B. 3.4
     * @param jahre 
     * @return Diskontierungssummenfaktor
     */
    double dsf( double zins, int jahre ) const;
    
    /**
     * Errechnet den Abzinsungsfaktor
     * @param zins
     * @param jahre
     * @return 
     */
    double abf( double zins, int jahre ) const;
};

#endif	/* CALCULATOR_H */

