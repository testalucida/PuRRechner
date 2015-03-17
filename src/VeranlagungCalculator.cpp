/* 
 * File:   VeranlagungCalculator.cpp
 * Author: max
 * 
 * Created on 15. März 2015, 12:08
 */

#include "VeranlagungCalculator.h"
#include "Vertraege.h"
#include "MainWindow.h"
#include "VeranlagungParm.h"
#include "VeranlagungTableData.h"

#include <my/datetime.h>
#include <my/datetimecalculator.h>
#include <my/convert.h>

using namespace my;

VeranlagungCalculator::VeranlagungCalculator( ) {
}

void VeranlagungCalculator::
     onRefreshVeranlagung( MainWindow &win, VeranlagungParm &parm ) 
{
    VeranlagungTableDataPtr p( new VeranlagungTableData() );
    
    VertragPtrVectorPtr pVertraege = _pVertraegeTableData->getVertraege();
    const char **ppColNames = VeranlagungsdatenHeaderNames;
    int jahresmietSumme = 0;
    int afaSumme = 0;
    int steuerlErgebSumme = 0;
    int steuerSumme = 0;
    int veraeussGewinnSumme = 0;
    for( auto v : *pVertraege ) {
        if( parm.jahr <= v->Mietende.GetYear() ) {
            int days = getAnzahlMiettage( v->Mietbeginn, 
                                          v->Mietende, 
                                          parm.jahr );
            //je Vertrag eine Zeile in VertraegeTableData.
            //jeder Vertrag ist relevant bzgl. Miete und AfA.
            //Nur Verträge, die im Veranlagungsjahr zum Rückkauf anstehen,
            //sind relevant bzgl. Veräußerungsgewinn.
            int row = p->addRow();
            //ID des Vertrags:
            p->setValue( v->Vertrag.get(), row, ppColNames[VERANLAGG_VERTRAG] );
            //Jahresmieteinnahme:
            int jahresmiete = days * v->Tagesmiete * v->Menge;
            jahresmietSumme += jahresmiete;
            p->setValue( to_string( jahresmiete).c_str(), row, ppColNames[VERANLAGG_MIETE] );
            //AfA in Prozent:
            StringPtr pAfa = Convert::toString( v->AfA, "%.1f" );
            p->setValue( pAfa->c_str(), row, ppColNames[VERANLAGG_AFA_PROZ] );
            //AfA in Euro:
            float afa = (v->AfA * v->Gesamtpreis / 100);
            afa *= ((float)days/(float)365); //AfA nur für die Tage, für die auch Mieteinnahmen erzielt wurden
            afaSumme += afa;
            p->setValue( to_string( (int)afa ).c_str(), row, ppColNames[VERANLAGG_AFA_EURO] );
            //Jahr des Rückkaufs:
            p->setValue( to_string( v->Mietende.GetYear() ).c_str(), row, ppColNames[VERANLAGG_RUECKKAUF] );
            //Wenn Jahr des Rückkaufs == Veranlagungsjahr, dann Veräußerungsgewinn:
            int veraeussGewinn = 0;
            if( parm.jahr == v->Mietende.GetYear() ) {
                veraeussGewinn = v->Veraeusserungsgewinn;
                veraeussGewinnSumme += veraeussGewinn;
                p->setValue( to_string( veraeussGewinn ).c_str(), row, 
                             ppColNames[VERANLAGG_VERAEUSSGEWINN] );
            } 
            //steuerliches Ergebnis:
            //setzt sich so zusammen: jahresmiete + Veräußerungsgewinn - AfA.
            int steuerlErgeb = jahresmiete + veraeussGewinn - afa;
            steuerlErgebSumme += steuerlErgeb;
            p->setValue( to_string( steuerlErgeb ).c_str(), row, ppColNames[VERANLAGG_STEUERL_ERGEBNIS] );
            
            //Steuer in Euro:
            int steuer = (parm.steuersatz * steuerlErgeb)/100;
            steuerSumme += steuer;
            p->setValue( to_string( steuer ).c_str(), row, ppColNames[VERANLAGG_STEUER] );
        }
    }
    
    //Summenzeile:
    int row = p->addRow();
     p->setValue( "SUMMEN", row, ppColNames[VERANLAGG_VERTRAG] );
     p->setValue( to_string( jahresmietSumme).c_str(), row, ppColNames[VERANLAGG_MIETE] );
     p->setValue( to_string( afaSumme ).c_str(), row, ppColNames[VERANLAGG_AFA_EURO] );
     p->setValue( to_string( steuerlErgebSumme ).c_str(), row, ppColNames[VERANLAGG_STEUERL_ERGEBNIS] );
     p->setValue( to_string( steuerSumme ).c_str(), row, ppColNames[VERANLAGG_STEUER] );
     p->setValue( to_string( veraeussGewinnSumme ).c_str(), row, ppColNames[VERANLAGG_VERAEUSSGEWINN] );
    
    p->sort( 4, SORTDIRECTION_ASC );
    win.setVeranlagungsdaten( p );
}

int VeranlagungCalculator::
    getAnzahlMiettage( 
                   const MyDate &mietbeginn, 
                   const MyDate &mietende,
                   int veranlagungsjahr ) const 
{
    
    MyDate vjahrBeginn( 1, 1, veranlagungsjahr );
    MyDate vjahrEnde( 31, 12, veranlagungsjahr );
    
    //Plausi: wenn der Mietbeginn erst nach dem Veranl.jahr liegt, oder das 
    // Mietende vor dem Veranl.jahr, dann geben wir 0 Tage Mietzeit zurück:
    if( mietbeginn > vjahrEnde || mietende < vjahrBeginn ) return 0;
    
    //Wir unterstellen erstmal 365 Miettage.
    //Wenn der tatsächliche Mietebeginn nach dem 1.1. des Veranlagungsjahres liegt, 
    //ziehen wir die Tage zwischen dem 1.1. und dem tatsächlichem Mietbeginn von
    //den 365 ab.
    //Liegt das Mietende vor dem 31.12., ziehen wir die Tage zwischen dem Mietende
    //und dem 31.12. ab.
    
    int days = 365;
    
    if( mietbeginn > vjahrBeginn ) {
        int d = DateTimeCalculator::GetDuration( vjahrBeginn, mietbeginn );
        days -= d;
    }
    
    if( mietende < vjahrEnde ) {
        int d = DateTimeCalculator::GetDuration( mietende, vjahrEnde );
        days -= d;
    }
    
    return days;
}

VeranlagungCalculator::~VeranlagungCalculator( ) {
}

