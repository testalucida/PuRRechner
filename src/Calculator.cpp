/* 
 * File:   Calculator.cpp
 * Author: max
 * 
 * Created on 7. Februar 2015, 16:08
 */

#include "Calculator.h"
#include <math.h>

Calculator::Calculator( ) {
}

void Calculator::onCalculate( IRendite &rendite, CalculationData &data ) {
    rendite.setRenditeOhneAfA( calculateOhneAfa( data ) );
    
    if( data.Steuersatz > 0 ) {
        rendite.setRenditeMitAfA( calculateMitAfa( data ) );
    }
    
    
}

float Calculator::calculateOhneAfa( const CalculationData &data ) const {
    //1. Jahresmiete berechnen
    //2. Rückkaufswert auf Zeitpunkt 0 abzinsen
    //3. Für jedes Jahr die Jahresmiete auf Zeitpunkt 0 abzinsen
    
    //4. Mit einem angenommenen Zinssatz von 1.0% beginnen und die Summe
    //   der abgezinsten Werte mit dem Kaufpreis vergleichen.
    //   Den Zinssatz solange erhöhen, bis der Vergleich der abgezinsten
    //   werte mit dem Kaufpreis 0 ergibt.
    //   Dieser Zinssatz ist die Rendite ohne AfA/Steuer.
    
    double jahresMiete = data.MieteProTag * 365;
    double mieteAbgezinst = 0;
    double rueckkaufAbgezinst = 0;
    double c0 = 0;
    double step = 0.005;
    double zins = 0.01;
    for( ; c0 <= 0 && zins < 50.00 /*willkürlich*/; zins += step ) {
        mieteAbgezinst = jahresMiete * dsf( zins, data.JahreLaufzeit );
        rueckkaufAbgezinst = data.Rueckkaufpreis * abf( zins, data.JahreLaufzeit );
        c0 = data.Einzelpreis - mieteAbgezinst - rueckkaufAbgezinst;
    }
    
    return zins;
}

float Calculator::calculateMitAfa( const CalculationData &data ) const {
    double jahresMiete = data.MieteProTag * 365;
    double mieteAbgezinst = 0;
    double rueckkaufAbgezinst = 0;
    double c0 = 0;
    double step = 0.005;
    //von der Jahresmiete die AfA abziehen. Es ergeben sich die jährlichen
    //stpfl. Einkünfte, die in der Regel negativ sind; sie sind aus Sicht
    //des Investors Einzahlungen und werden mit dem DSF auf den Zeitpunkt 0
    //abgezinst.
    double afaWert = (double)((data.AfA * data.Einzelpreis)/100);
    double jhrlSteuerlast = (jahresMiete - afaWert) *  (double)(data.Steuersatz/100);
    double jhrlSteuerlastAbgezinst = 0;
    //Steuerpflichtiger Gewinn ergibt sich nach 5 Jahren aus dem Rückkaufswert
    //abzüglich Restbuchwert.
    //Der Restbuchwert ergibt sich aus dem Kaufpreis abzgl. AfA x Anzahl der Miet-Jahre.
    //Der stpfl. Gewinn x Steuersatz ist aus Sicht des Investors eine Auszahlung.
    //Diese Auszahlung, die einmalig nach 5 Jahren fällig ist, wird abgezinst auf
    //den Zeitpunkt 0.
    double gesamtAbschreibung = afaWert * data.JahreLaufzeit;
    double restbuchwert = data.Einzelpreis - gesamtAbschreibung;
    double steuerSchlussZahlung = 
        (data.Rueckkaufpreis - restbuchwert ) * (double)(data.Steuersatz/100);
    double steuerSchlussZahlungAbgezinst = 0;
    double zins = 0.01;
    for( ; c0 <= 0 && zins < 50.00 /*willkürlich*/; zins += step ) {
        mieteAbgezinst = jahresMiete * dsf( zins, data.JahreLaufzeit );
        rueckkaufAbgezinst = data.Rueckkaufpreis * abf( zins, data.JahreLaufzeit );
        jhrlSteuerlastAbgezinst = jhrlSteuerlast * dsf( zins, data.JahreLaufzeit );
        steuerSchlussZahlungAbgezinst = steuerSchlussZahlung * abf( zins, data.JahreLaufzeit );
        c0 = data.Einzelpreis + steuerSchlussZahlungAbgezinst + jhrlSteuerlastAbgezinst - 
             mieteAbgezinst - rueckkaufAbgezinst;
    }
    
    return zins;
}

double Calculator::dsf( double zins, int jahre ) const {
    double q = 1 + zins/100;
    double qhochn = pow( q, (double)jahre );
    double dsf = (qhochn - 1) / (qhochn * zins/100);
   
    return dsf;
}

double Calculator::abf( double zins, int jahre ) const {
    double q = 1 + zins/100;
    double abf = pow( q, (jahre*(-1) ) );
    return abf;
}

Calculator::~Calculator( ) {
}

