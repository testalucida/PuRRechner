/* 
 * File:   MainWindow.cpp
 * Author: max
 * 
 * Created on 20. April 2014, 23:23
 */

#include "MainWindow.h"
#include "Vertrag.h"
#include "../images/save.xpm"
#include "../images/save_deact.xpm"
#include "../images/rubbish.xpm"  
#include "../images/rubbish_deact.xpm"  

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
#include <FL/Fl_Pixmap.H>

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
: Flx_Window( x, y, 1100, 850, "Container Kalkulation und Verwaltung" )
, _yspacing( 10 )
, _xspacing( 10 )
, _statusbarHeight( 25 )
, _toolbarHeight( 30 )
, _inputHeight( 21 )
{
    _pToolBar = new Flx_ToolBar( 0, 0, w(), _toolbarHeight );
    _pToolBar->addButton( NULL, NULL, "" ).deactivate(); //Dummy wg. Abstand zum Rand
    _pBtnSave = &( _pToolBar->addButton( save_xpm, save_deact_xpm, "Vertrag speichern" ) );
    _pBtnSave->deactivate();
    _pBtnDelete = &( _pToolBar->addButton( rubbish_xpm, rubbish_deact_xpm, "Vertrag löschen" ) );
    _pBtnDelete->deactivate();
    _pToolBar->signalToolButtonSelected.connect<MainWindow, &MainWindow::onToolButtonSelected>( this );
    
    Flx_Group &contGrp = createTopGroup();
    
    Flx_Group &vertrGrp  = 
            createAlleVertraegeGroup( contGrp.x(), 
                                      contGrp.y() + contGrp.h() + _yspacing, 
                                      contGrp.w(), 
                                      320 );
    
    int H = this->h() - vertrGrp.y() - vertrGrp.h() - 3*_yspacing;
    Flx_Group &depotGrp = createDepotGroup( vertrGrp.x(), vertrGrp.y() + vertrGrp.h() + _yspacing, 
                                            400, //vertrGrp.w()/2, 
                                            H );
    
    Flx_Group &steuerGrp = createSteuerGroup( depotGrp.x() + depotGrp.w() + _xspacing, 
                                              depotGrp.y(), 
                                              w() - depotGrp.w() - 3*_xspacing, 
                                              depotGrp.h() );

    end();
    resizable( vertrGrp );
    
    _pLaufzeit->value( "5" );
    //->value( 10.0 );
    _pAfaChoice->value( 0 );
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
                                        240 /*380*/ );                                     
    pTopGrp->box( FL_BORDER_BOX );
    pTopGrp->color( fl_lighter( FL_LIGHT2 ) );
    
    ////////// Container Group
    Flx_Group &grp = createContainerGroup( pTopGrp->x() + _xspacing,
                              pTopGrp->y() + _yspacing,
                              pTopGrp->w() - 2*_xspacing,
                              90 + 2*_yspacing /*120*/ );
    
    /////////  Calculation Group
    Flx_Group &grp2 = createCalculationGroup( grp.x() + 450, //grp.w() + _xspacing, 
                                              grp.y() + _yspacing,
                                              600, //pTopGrp->w() - grp.w() - 3*_xspacing,
                                              //530, //grp.w(), 
                                              90 );
//    Flx_Group &grp2 = createCalculationGroup( grp.x(), grp.y() + grp.h() + _yspacing,
//                                              530, //grp.w(), 
//                                              90 );
    
    grp.add( grp2 );
    
    ////////// Vertrag Group
    createVertragGroup( grp.x(), 
                        grp.y() + grp.h() + _yspacing,
                        grp.w(), 
                        100 /*90*/ );
        
    pTopGrp->end();
    return *pTopGrp;
}

//Flx_Group &MainWindow::createContainerGroup( int x, int y, int w, int h ) {
//    Flx_Group *p = new Flx_Group( x, y, w, h, "Container" );
//    p->box( FL_BORDER_BOX );
//    p->color( FL_LIGHT2 );
//    p->labeltype( FL_EMBOSSED_LABEL );
//    p->labelfont( 2 );
//    p->align( Fl_Align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE ) );
//    
//    ////////// Einzelpreis
//    int X = x + 110;
//    int Y = y + 2*_yspacing;
//    _pEinzelpreis = (Flx_FloatInput*)createInput( X, Y, 60, INPUT_FLOAT, "Einzelpreis: " );
//    
//    ////////// Miete pro Tag
//    X = _pEinzelpreis->x() + _pEinzelpreis->w() + 150;
//    _pMieteContTag = (Flx_FloatInput*)createInput( X, Y, 60, INPUT_FLOAT, "Miete/Cont/Tag: " );
//    
//    ///////// Laufzeit
//    X = _pMieteContTag->x() + _pMieteContTag->w() + 150;
//    _pLaufzeit = (Flx_IntInput*)createInput( X, Y, 30, INPUT_INT, "Laufzeit (Jahre): " );
//    
//    ///////// Rückkaufswert
//    X = _pLaufzeit->x() + _pLaufzeit->w()  + 110;
//    _pRueckkauf = (Flx_FloatInput*)createInput( X, Y, 60, INPUT_FLOAT, "Rückkauf: " );
//
//    p->end();
//
//    return *p;
//}

Flx_Group &MainWindow::createContainerGroup( int x, int y, int w, int h ) {
    Flx_Group *p = new Flx_Group( x, y, w, h, "Container" );
    p->box( FL_BORDER_BOX );
    p->color( FL_LIGHT2 );
    p->labeltype( FL_EMBOSSED_LABEL );
    p->labelfont( 2 );
    p->align( Fl_Align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE ) );
    
    ////////// 1. Spalte: Einzelpreis, Miete
    int X = x + 110;
    int Y = y + 3*_yspacing;
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
    pGrp->color( fl_lighter( FL_LIGHT2 ) );
    
    /////////// Zeile 1: AfA,  persönl. Steuersatz, Berechnen-Button
     _pAfaChoice = new Flx_Choice( x + 110, y + 2*_yspacing, 60, 25, "AfA (%): " );
     _pAfaChoice->color( FL_WHITE );
     _pAfaChoice->add( "10.0" );
     _pAfaChoice->add( "12.5" );
//    _pAfa = (Flx_FloatInput*)createInput( x + 110, y + 2*_yspacing, 50, 
//                                          INPUT_FLOAT, "AfA (%): " );
    
    _pSteuersatz = (Flx_FloatInput*)createInput( _pAfaChoice->x() + _pAfaChoice->w() + 170,
                                                 _pAfaChoice->y(), 50, 
                                                INPUT_FLOAT, "Steuersatz (%): " );
    
    _pBtnRendite = new Flx_Button( _pSteuersatz->x() + _pSteuersatz->w() + _xspacing, 
                                   _pSteuersatz->y(),
                                   125, _inputHeight, 
                                   "Rendite berechnen" );
    _pBtnRendite->signalSelected.connect<MainWindow, &MainWindow::onBtnRenditePushed>( this );
    
    /////////// Zeile 2: Rendite mit AfA/Steuer, Rendite ohne AfA/Steuer
    _pRenditeMit = (Flx_Output*)createInput( _pAfaChoice->x(), 
                                             _pAfaChoice->y() + _pAfaChoice->h() + _yspacing, 
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
//    _pBtnRendite = new Flx_Button( _pAfa->x(), 
//                                _pRenditeMit->y() + _pRenditeMit->h() + _yspacing,
//                                270, _inputHeight, "Rendite berechnen" );
//    _pBtnRendite->signalSelected.connect<MainWindow, &MainWindow::onBtnRenditePushed>( this );
   
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
    _pAngebot = (Flx_Input*)createInput( x + 110, y + 3*_yspacing, 80, 
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
//    _pBtnSave = new Flx_Button( _pMietbeginn->x(),
//                                _pMietbeginn->y() + _pMietbeginn->h() + _yspacing,
//                                270, _inputHeight, "Containervertrag speichern" );
//    _pBtnSave->signalSelected.connect<MainWindow, &MainWindow::onBtnSavePushed>( this );
//    _pBtnSave->deactivate();

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
 
 flx::Flx_Group &MainWindow::createAlleVertraegeGroup( int x, int y, int w, int h ) {
    Flx_Group *pGrp  = new Flx_Group( x, y, w, h, "Vertragsbestand" );
    pGrp->box(FL_BORDER_BOX);
    pGrp->color( fl_lighter( FL_LIGHT2 ) );
    pGrp->labeltype( FL_EMBOSSED_LABEL );
    pGrp->labelfont( 2 );
    pGrp->align( Fl_Align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE ) );

    _pTable = new Flx_Table( x + _xspacing, y + _yspacing + 10, 
                            w - 2*_xspacing, h - 2*_yspacing - 10 ); //- 50 );
    _pTable->box(FL_THIN_DOWN_FRAME);
    _pTable->color(FL_LIGHT2);
    _pTable->selection_color(FL_BACKGROUND_COLOR);
    _pTable->labeltype(FL_NORMAL_LABEL);
    _pTable->labelfont(0);
    _pTable->labelsize(11);
    _pTable->labelcolor(FL_FOREGROUND_COLOR);
    _pTable->row_header( 0 );
    _pTable->align(Fl_Align(FL_ALIGN_TOP));
    _pTable->setSelectionMode( FLX_SELECTION_SINGLEROW );
    _pTable->setSortable( true );
    _pTable->signalSelected.connect<MainWindow, &MainWindow::onVertraegeTableSelectionChanged>( this );
    pGrp->end();
    
    return *pGrp;
 }

flx::Flx_Group &MainWindow::createDepotGroup( int x, int y, int w, int h ) {
    Flx_Group *pGrp  = new Flx_Group( x, y, w, h, "Depot" );
    pGrp->box(FL_BORDER_BOX);
    pGrp->color( fl_lighter( FL_LIGHT2 ) );
    pGrp->labeltype( FL_EMBOSSED_LABEL );
    pGrp->labelfont( 2 );
    pGrp->align( Fl_Align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE ) );
    
    _pAnzahlAktiveVertraege = new Flx_Output( x + 175, 
                                      y + 2*_yspacing, 
                                      25, 25, "Aktive Verträge: " );
    _pAnzahlAktiveVertraege->value( "0" );
    
    _pSummeInvest = new Flx_Output( _pAnzahlAktiveVertraege->x(), 
                                      _pAnzahlAktiveVertraege->y() + _pAnzahlAktiveVertraege->h() + _yspacing, 
                                      55, 25, "Summe Investitionen: "  );
    
    _pDepotZeitwert = new Flx_Output( _pAnzahlAktiveVertraege->x(), 
                                      _pSummeInvest->y() + _pSummeInvest->h() + _yspacing, 
                                      55, 25, "Zeitwert: " );
    _pDepotZeitwert->textfont( FL_HELVETICA_BOLD );
    
    
    _pDepotSummeRueckkauf = new Flx_Output( _pDepotZeitwert->x(),
                                            _pDepotZeitwert->y() + _pDepotZeitwert->h() + _yspacing, 
                                            55, 25, "Summe Rückkaufswerte: " );
   _pDepotSummeRueckkauf->textfont( FL_HELVETICA_BOLD );

    
    _pSumVeraeussGewinne = new Flx_Output( _pDepotSummeRueckkauf->x(),
                                           _pDepotSummeRueckkauf->y() + _pDepotSummeRueckkauf->h() + _yspacing, 
                                           55, 25, "Summe Veräuß.gewinne: " );
    _pSumVeraeussGewinne->textfont( FL_HELVETICA_BOLD );
    
    pGrp->end();
    
    return *pGrp;
}
 
flx::Flx_Group &MainWindow::createSteuerGroup( int x, int y, int w, int h ) {
    Flx_Group *pGrp  = new Flx_Group( x, y, w, h, "Steuerliche Auswirkungen" );
    pGrp->box(FL_BORDER_BOX);
    pGrp->color( fl_lighter( FL_LIGHT2 ) );
    pGrp->labeltype( FL_EMBOSSED_LABEL );
    pGrp->labelfont( 2 );
    pGrp->align( Fl_Align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE ) );
    
    _pJahrAuswahl = new Flx_Choice( x + 125, y + 2*_yspacing, 75, 25, "Veranlagungsjahr" );
    _pJahrAuswahl->color( FL_WHITE );
    
    _pSteuersatz2 = new Flx_IntInput( _pJahrAuswahl->x() + _pJahrAuswahl->w() + 100,
                                  _pJahrAuswahl->y(), 30, 25, "Steuersatz (%)" );
    _pSteuersatz2->value( "30" );

    int Y = _pJahrAuswahl->y() + _pJahrAuswahl->h() + _yspacing;
    _pSteuerTable = new Flx_Table( x + _xspacing, Y,
                                   w - 2*_xspacing, 
                                   y + h - Y - _yspacing );
    
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

void MainWindow::onToolButtonSelected( Flx_ToolBar &tb, ToolAction &action ) {
    
}

void MainWindow::onBtnRenditePushed( flx::Flx_Button &, flx::ActionParm & ) {
    CalculationData calcData;
    calcData.Einzelpreis = _pEinzelpreis->floatValue();
    calcData.JahreLaufzeit = _pLaufzeit->intValue();
    calcData.MieteProTag = _pMieteContTag->floatValue();
    calcData.Rueckkaufpreis = _pRueckkauf->floatValue();
    calcData.AfA = Convert::toFloat( _pAfaChoice->text() );
    //calcData.AfA = _pAfa->floatValue();
    calcData.Steuersatz = _pSteuersatz->floatValue();
    signalCalculateRendite.send( this, &calcData );
}

void MainWindow::onBtnSavePushed( flx::Flx_Button &, flx::ActionParm & ) {
    Vertrag vertrag;
    vertrag.Einzelpreis = _pEinzelpreis->floatValue();
    vertrag.Tagesmiete = _pMieteContTag->floatValue();
    vertrag.JahreMietdauer = _pLaufzeit->intValue();
    vertrag.Rueckkaufswert = _pRueckkauf->floatValue();
    vertrag.AfA = Convert::toFloat( _pAfaChoice->text() );
    //vertrag.AfA = _pAfa->floatValue();
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

void MainWindow::onVertraegeTableSelectionChanged( Flx_Table &, SelectionEvent &evt ) {
    _pBtnDelete->activate();
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
        //_pAfa->floatValue() > 0 &&        
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

void MainWindow::setVertraege( VertraegeTableData &vertraege ) {
    _pTable->setTableData( (TableData&)vertraege );
}

VertraegeTableData &MainWindow::getVertraege() const {
    return (VertraegeTableData&)_pTable->getTableData();
}

void MainWindow::setDepotData( DepotData depotData ) {
    _pAnzahlAktiveVertraege->
        value( to_string( depotData.AnzahlAktiveVertraege ).c_str() );
    
    _pSummeInvest->value( to_string( depotData.SummeInvest ).c_str() );
    
    _pDepotZeitwert->
        value( to_string( depotData.DepotwertHeute ).c_str() );
   
    _pDepotSummeRueckkauf->
        value( to_string( depotData.SummeRueckkaufwerte ).c_str() ); 
    
    _pSumVeraeussGewinne->
        value( to_string( depotData.SummeVeraeussGewinne ).c_str() );
   
}

void MainWindow::setVeranlagungsjahre( std::vector<int> &jahre ) {
    for( auto j : jahre ) {
        _pJahrAuswahl->add( to_string( j ).c_str() );
    }
    _pJahrAuswahl->value( 0 );
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

