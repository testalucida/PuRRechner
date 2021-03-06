/* 
 * File:   MainWindow.cpp
 * Author: max
 * 
 * Created on 20. April 2014, 23:23
 */

#include "MainWindow.h"
#include "Vertrag.h"

#include <flx/Flx_Group.h>
#include <flx/Flx_Choice.h>
#include <flx/Flx_IntInput.h>
#include <flx/Flx_FloatInput.h>
#include <flx/Flx_Input.h>
#include <flx/Flx_Box.h>
#include <flx/Flx_ToolBar.h>
#include <flx/Flx_Output.h>
#include <flx/Flx_DateChooser.h>
#include <flx/Flx_Button.h>
#include <flx/Flx_Table.h>
#include <flx/flx_signalparms.h>

#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/Fl.H>

#include <my/datetimecalculator.h>
#include <FL/Fl_Input_.H>
#include <my/datetime.h>
#include <my/convert.h>


using namespace flx;
using namespace my;

enum KindOfInput {
    INPUT_FLOAT,
    INPUT_INT,
    INPUT_ALPHA,
    INPUT_DATE,
    OUTPUT
};

MainWindow::MainWindow( int x, int y ) 
: Flx_Window( x, y, 800, 700, "Container Kalkulation und Verwaltung" )
, _yspacing( 10 )
, _xspacing( 10 )
, _statusbarHeight( 25 )
, _toolbarHeight( 25 )
, _inputHeight( 21 )
{
    _pToolBar = new Flx_ToolBar( 0, 0, w(), _toolbarHeight );
    //add( _pToolBar );
    Flx_Group &contGrp = createTopGroup();
    Flx_Group &botGrp = createBottomGroup( contGrp.x(), contGrp.y() + contGrp.h() + _yspacing,
                       contGrp.w(), this->h() - contGrp.y() - contGrp.h() - 2*_yspacing );
    end();
    resizable( botGrp );
    
    _pLaufzeit->value( "5" );
    _pAfa->value( 12.5 );
    _pSteuersatz->value( 30.0 );
    _pLfdNr->value( "0" );
    _pKunde->value( "M" );
    
      //TEST
//    _pEinzelpreis->value( 3380 );
//    _pMieteContTag->value( 1.15 );
//    _pAnzahl->value( "4" );
//    _pRueckkauf->value( 2065.0 );
//    _pAngebot->value( "1069" );
//    _pVertrag->value( "GC 101858" );
//    _pMietbeginn->setDate( "15.06.2012" );
//    _pMietende->value( "14.06.2017" );
    
    
    _pEinzelpreis->take_focus();
}

Flx_Group &MainWindow::createTopGroup() {
  
    Flx_Group *pTopGrp = new Flx_Group( _xspacing, _yspacing + _toolbarHeight, 
                                        w() - 2*_xspacing, 
                                        370 /*380*/ );                                     
    pTopGrp->box( FL_BORDER_BOX );
    pTopGrp->color( FL_LIGHT2 );
    Flx_Group &grp = createContainerGroup( pTopGrp->x() + _xspacing,
                              pTopGrp->y() + _yspacing,
                              pTopGrp->w() - 2*_xspacing,
                              90 /*120*/ );
    Flx_Group &grp2 = createCalculationGroup( grp.x(), grp.y() + grp.h() + _yspacing,
                              grp.w(), 120 );
    
    createVertragGroup( grp2.x(), grp2.y() + grp2.h() + _yspacing,
                              grp2.w(), 120 /*90*/ );
        
    pTopGrp->end();
    return *pTopGrp;
}

Flx_Group &MainWindow::createContainerGroup( int x, int y, int w, int h ) {
    Flx_Group *p = new Flx_Group( x, y, w, h, "Container" );
    p->box( FL_BORDER_BOX );
    p->color( FL_LIGHT2 );
    p->labeltype( FL_EMBOSSED_LABEL );
    p->labelfont( 2 );
    p->align( Fl_Align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE ) );
    
    ////////// Spalte 1: Einzelpreis, Miete
    int X = x + 110;
    int Y = y + 2*_yspacing;
    _pEinzelpreis = (Flx_FloatInput*)createInput( X, Y, 
                                                  60, INPUT_FLOAT, "Einzelpreis: " );
    
    Y = _pEinzelpreis->y() + _pEinzelpreis->h() + _yspacing;
    _pMieteContTag = (Flx_FloatInput*)createInput( _pEinzelpreis->x(), 
                                                  Y, 60, INPUT_FLOAT, 
                                                  "Miete/Cont/Tag: " );
    
    ///////// 2. Spalte: Laufzeit, Rückkauf
    _pLaufzeit = (Flx_IntInput*)createInput( 350, 
                                             _pEinzelpreis->y(), 
                                             30, INPUT_INT, "Laufzeit (Jahre): " );
    
    Y = _pLaufzeit->y() + _pLaufzeit->h() + _yspacing; 
    _pRueckkauf = (Flx_FloatInput*)createInput( _pLaufzeit->x(), 
                                                Y, 
                                                60, INPUT_FLOAT, "Rückkauf: " );

    p->end();

    return *p;
}

Flx_Group &MainWindow::createCalculationGroup( int x, int y, int w, int h ) {
    Flx_Group *pGrp = new Flx_Group( x, y, w, h, "Kalkulation" );
    pGrp->labeltype( FL_EMBOSSED_LABEL );
    pGrp->labelfont( 2 );
    pGrp->align( Fl_Align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE ) );
    pGrp->box( FL_BORDER_BOX );
    pGrp->color( FL_LIGHT2 );
    
    /////////// Zeile 1: AfA und persönl. Steuersatz
    _pAfa = (Flx_FloatInput*)createInput( x + 110, y + 2*_yspacing, 50, 
                                          INPUT_FLOAT, "AfA (%): " );
    _pSteuersatz = (Flx_FloatInput*)createInput( _pAfa->x() + _pAfa->w() + 170,
                                                 _pAfa->y(), 50, 
                                                INPUT_FLOAT, "Steuersatz (%): " );
    
    /////////// Zeile 2: Rendite mit AfA/Steuer, Rendite ohne AfA/Steuer
    _pRenditeMit = (Flx_Output*)createInput( _pAfa->x(), 
                                             _pAfa->y() + _pAfa->h() + _yspacing, 
                                             50, OUTPUT, 
                                             "Rendite(%): " );
    Flx_Box *pBoxMit = new Flx_Box( _pRenditeMit->x() + _pRenditeMit->w() + 5,
                                    _pRenditeMit->y(), 100, _inputHeight, "mit AfA/Steuer" );
    pBoxMit->color( pGrp->color() );
    
    _pRenditeOhne = (Flx_Output*)createInput( _pSteuersatz->x(), 
                                             _pRenditeMit->y(), 
                                             50, OUTPUT, "" );
    Flx_Box *pBoxOhne = new Flx_Box( _pRenditeOhne->x() + _pRenditeOhne->w() + 5,
                                    _pRenditeOhne->y(), 100, _inputHeight, "ohne AfA/Steuer" );
    pBoxOhne->color( pGrp->color() );  
    
    /////////// Zeile 3: Button "Rendite berechnen"
    _pBtnRendite = new Flx_Button( _pAfa->x(), 
                                _pRenditeMit->y() + _pRenditeMit->h() + _yspacing,
                                270, _inputHeight, "Rendite berechnen" );
    _pBtnRendite->signalSelected.connect<MainWindow, &MainWindow::onBtnRenditePushed>( this );
   
    pGrp->end();
      
    return *pGrp;
}

Flx_Group &MainWindow::createVertragGroup( int x, int y, int w, int h ) {
    Flx_Group *pGrp = new Flx_Group( x, y, w, h, "Vertragsdaten" );
    pGrp->labeltype( FL_EMBOSSED_LABEL );
    pGrp->labelfont( 2 );
    pGrp->align( Fl_Align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE ) );
    pGrp->box( FL_BORDER_BOX );
    pGrp->color( FL_LIGHT2 );
    
    /////////// Zeile 1: Angebot, Vertragsnummer, Kunde
    _pAngebot = (Flx_Input*)createInput( x + 110, y + 2*_yspacing, 80, 
                                          INPUT_ALPHA, "Angebot: " );
    
    _pVertrag = (Flx_Input*)createInput( _pAngebot->x() + _pAngebot->w() + 160,
                                                 _pAngebot->y(), 90, 
                                                INPUT_ALPHA, "Vertrag: " );
    
    _pLfdNr = (Flx_IntInput*)createInput( _pVertrag->x() + _pVertrag->w() + 65,
                                          _pVertrag->y(), 20,
                                          INPUT_INT, "LfdNr: " );
    
    _pKunde = (Flx_Input*)createInput( _pVertrag->x() + _pVertrag->w() + 160,
                                       _pVertrag->y(), 45,
                                       INPUT_ALPHA, "Kunde: " ); 
    
    //////////////////// Zeile 2:   Mietbeginn und Mietende, Anzahl
    
    _pMietbeginn = (Flx_DateChooser*)createInput( _pAngebot->x(), 
                                                  _pAngebot->y() + _pAngebot->h() + _yspacing, 
                                                  90, INPUT_DATE, "Mietbeginn: " );
    
    _pMietende = (Flx_Output*)createInput( _pVertrag->x(), _pMietbeginn->y(), 
                                           90, OUTPUT, "Mietende: ");
    
    _pAnzahl = (Flx_IntInput*)createInput( _pKunde->x(), _pMietende->y(), 45,
                                            INPUT_INT, "Anzahl: " );
    
    /////////// Zeile 3: Button "Containervertrag speichern"
    _pBtnSave = new Flx_Button( _pMietbeginn->x(),
                                _pMietbeginn->y() + _pMietbeginn->h() + _yspacing,
                                270, _inputHeight, "Containervertrag speichern" );
    _pBtnSave->signalSelected.connect<MainWindow, &MainWindow::onBtnSavePushed>( this );
    _pBtnSave->deactivate();

    pGrp->end();
    return *pGrp;
}

Fl_Widget *MainWindow::createInput( int x, int y, int w, int kindInput, const char *lbl ) {
    Fl_Widget *p;
    switch( kindInput ) {
        case INPUT_FLOAT:
            p = new Flx_FloatInput( x, y, w, _inputHeight, lbl );
            ((Flx_FloatInput*)p)->justify( FL_ALIGN_RIGHT );
           
            ((Flx_FloatInput*)p)->signalChanged.
                    connect<MainWindow, &MainWindow::onNumericInputChanged>( this );
            break;
        case INPUT_INT:
            p = new Flx_IntInput( x, y, w, _inputHeight, lbl );
            ((Flx_IntInput*)p)->justify( FL_ALIGN_RIGHT );
            ((Flx_IntInput*)p)->signalChanged.
                    connect<MainWindow, &MainWindow::onNumericInputChanged>( this );
            break;
        case INPUT_ALPHA:
            p = new Flx_Input( x, y, w, _inputHeight, lbl );
            ((Flx_Input*)p)->signalChanged.
                    connect<MainWindow, &MainWindow::onAlphaInputChanged>( this );
            break;
        case INPUT_DATE:
            p = new Flx_DateChooser( x, y, _inputHeight, lbl );
            ((Flx_DateChooser*)p)->signalDateSelected.
                    connect<MainWindow, &MainWindow::onMietbeginnChanged>( this );
            break;
        case OUTPUT:
            p = new Flx_Output( x, y, w, _inputHeight, lbl );
            break;
        default:
            break;
    }
    //p->box( FL_FLAT_BOX );
    return p;
}

 Flx_Group &MainWindow::createBottomGroup( int x, int y, int w, int h ) {
    Flx_Group *pGrp  = new Flx_Group( x, y, w, h, "Vertragsbestand" );
    pGrp->box(FL_BORDER_BOX);
    pGrp->color(FL_LIGHT2);
    pGrp->labeltype( FL_EMBOSSED_LABEL );
    pGrp->labelfont( 2 );
    pGrp->align( Fl_Align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE ) );

    _pTable = new Flx_Table( x + _xspacing, y + _yspacing + 10, 
                            w - 2*_xspacing, h - 2*_yspacing - 50 );
    _pTable->box(FL_THIN_DOWN_FRAME);
    _pTable->color(FL_LIGHT2);
    _pTable->selection_color(FL_BACKGROUND_COLOR);
    _pTable->labeltype(FL_NORMAL_LABEL);
    _pTable->labelfont(0);
    _pTable->labelsize(11);
    _pTable->labelcolor(FL_FOREGROUND_COLOR);
    _pTable->row_header( 0 );
    _pTable->align(Fl_Align(FL_ALIGN_TOP));
    //_pTable->when(FL_WHEN_RELEASE);
    _pTable->setSelectionMode( FLX_SELECTION_SINGLEROW );
    
    _pDepotZeitwert = new Flx_Output( _pTable->x(), 
                                      _pTable->y() + _pTable->h() + _yspacing, 
                                      55, 25, "Zeitwert des Depots " );
   
    _pDepotZeitwert->textfont( FL_HELVETICA_BOLD );
    _pDepotZeitwert->align( FL_ALIGN_RIGHT );
    
    _pDepotSummeRueckkauf = new Flx_Output( _pDepotZeitwert->x() + 200,
                                            _pDepotZeitwert->y(), 
                                            55, 25, "Summe d. Rückkaufswerte (stpfl. ab Kauf 2009)" );
    _pDepotSummeRueckkauf->textfont( FL_HELVETICA_BOLD );
    _pDepotSummeRueckkauf->align( FL_ALIGN_RIGHT );
            
    
     pGrp->end();
     pGrp->resizable( _pTable );
     return *pGrp;
 }

int MainWindow::getTextLen( const char *txt ) const {
    int w=0, h=0;
    fl_measure( txt, w, h, 0 );
    return w;
}

void MainWindow::adjustX( int nWidgets, int left, ... ) {
    va_list list;
    va_start( list, left );
    int maxx = left + _xspacing;
    for( int i = 0; i < nWidgets; i++ ) {
        Fl_Widget *p = va_arg( list, Fl_Widget* );
        maxx = ( p->x() > maxx ) ? p->x() : maxx; 
    }
    
    va_start( list, left );
    for( int i = 0; i < nWidgets; i++ ) {
        Fl_Widget *p = va_arg( list, Fl_Widget* );
        p->position( maxx, p->y() );
    }
    
    va_end( list );
}

void MainWindow::onBtnRenditePushed( flx::Flx_Button &, flx::ActionParm & ) {
    CalculationData calcData;
    calcData.Einzelpreis = _pEinzelpreis->floatValue();
    calcData.JahreLaufzeit = _pLaufzeit->intValue();
    calcData.MieteProTag = _pMieteContTag->floatValue();
    calcData.Rueckkaufpreis = _pRueckkauf->floatValue();
    calcData.AfA = _pAfa->floatValue();
    calcData.Steuersatz = _pSteuersatz->floatValue();
    signalCalculateRendite.send( this, &calcData );
}

void MainWindow::onBtnSavePushed( flx::Flx_Button &, flx::ActionParm & ) {
    Vertrag vertrag;
    vertrag.Einzelpreis = _pEinzelpreis->floatValue();
    vertrag.Tagesmiete = _pMieteContTag->floatValue();
    vertrag.JahreMietdauer = _pLaufzeit->intValue();
    vertrag.Rueckkaufswert = _pRueckkauf->floatValue();
    vertrag.AfA = _pAfa->floatValue();
    vertrag.Angebot.add( _pAngebot->value() );
    vertrag.Vertrag.add( _pVertrag->value() );
    vertrag.LfdNr = _pLfdNr->intValue();
    vertrag.Kunde.add( _pKunde->value() );
    vertrag.Menge = _pAnzahl->intValue();
    vertrag.Mietbeginn.FromDate( _pMietbeginn->getDate() );
    vertrag.Mietende.FromEurString( _pMietende->value() );
    signalSaveVertrag.send( *this, vertrag );
    _pBtnSave->deactivate();
}

void MainWindow::onNumericInputChanged( flx::Flx_NumericInput &inp, flx::ActionParm & ) {
    if( &inp == _pEinzelpreis ) {
      
    } else if( &inp == _pLaufzeit ) {
        int nJahre = _pLaufzeit->intValue();
        if( nJahre > 0 ) {
            const MyDate &beginn = _pMietbeginn->getDate();
            MyDate ende( beginn );
            DateTimeCalculator::ComputeYears( ende, nJahre );
            _pMietende->const_value( ende.ToEurString() );    
        } else {
            _pMietende->value( "" );            
        }
    }
    
    checkSaveButton();
}

void MainWindow::onMietbeginnChanged( Flx_DateChooser &, my::MyDate &date ) {
    int nJahre = _pLaufzeit->intValue();
    if( nJahre > 0 ) {
        MyDate ende( date );
        DateTimeCalculator::ComputeYears( ende, nJahre );
        _pMietende->const_value( ende.ToEurString() );
    }
}

void MainWindow::onAlphaInputChanged( flx::Flx_Input &inp, flx::ActionParm & ) {
    checkSaveButton();
} 

bool MainWindow::canSave() const {
     if( strlen( _pVertrag->value() ) > 0 &&
        strlen( _pAngebot->value() ) > 0 &&
        strlen( _pKunde->value() ) > 0 &&
        _pAnzahl->intValue() > 0 &&
        _pAfa->floatValue() > 0 &&        
        _pEinzelpreis->floatValue() > 0 &&
        _pMieteContTag->floatValue() > 0 &&
        _pLaufzeit->intValue() > 0 &&
        _pRueckkauf->floatValue() > 0 ) 
    {
        return true;
    } 
    
    return false;
}

void MainWindow::checkSaveButton() {
    if( canSave() ) {
        _pBtnSave->activate();
    } else {
        _pBtnSave->deactivate();
    }
}

//void MainWindow::computeMietende( const my::MyDate &beginn, my::MyDate &ende ) {
//    
//}

void MainWindow::setRenditeOhneAfA( float rendite ) {
    char buf[10];
    sprintf( buf, "%.2f", rendite );
    _pRenditeOhne->value( buf );
}

void MainWindow::setRenditeMitAfA( float rendite ) {
    char buf[10];
    sprintf( buf, "%.2f", rendite );
    _pRenditeMit->value( buf );
}

void MainWindow::setVertraege( Vertraege &vertraege ) {
    _pTable->setTableData( (TableData&)vertraege );
}

Vertraege &MainWindow::getVertraege() const {
    return (Vertraege&)_pTable->getTableData();
}

void MainWindow::setDepotWert( DepotWert depotWert ) {
    string wert;
    _pDepotZeitwert->value( Convert::toString( depotWert.DepotwertHeute, wert ).c_str() );
    wert.clear();
    _pDepotSummeRueckkauf->value( Convert::toString( depotWert.SummeRueckkaufwerte, wert ).c_str() ); 
}

void MainWindow::clear() {
    _pEinzelpreis->value( 0.00 );
    _pAnzahl->value( "0" );
    _pMieteContTag->value( 0.00 );
    _pRueckkauf->value( 0.00 );
    _pLfdNr->value( "0" );
    _pAngebot->value( "" );
    _pVertrag->value( "" );
    _pKunde->value( "M" );
}

MainWindow::~MainWindow( ) {
}

