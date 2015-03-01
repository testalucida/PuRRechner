/* 
 * File:   MainWindow.h
 * Author: max
 *
 * Created on 20. April 2014, 23:23
 */

#ifndef MAINWINDOW_H
#define	MAINWINDOW_H

#include <flx/Flx_Window.h>
#include <my/Signal.hpp>

#include <stdarg.h>
#include "CalculationData.h"
#include "Vertrag.h"
#include "DepotWertCalculator.h"

namespace flx {
    class Flx_Group;
    class Flx_ToolBar;
    class Flx_NumericInput;
    class Flx_FloatInput;
    class Flx_IntInput;
    class Flx_Input;
    class Flx_Output;
    class Flx_DateChooser;
    class Flx_Button;
    class Flx_Table;
    class Flx_DateChooser;
    struct ActionParm;
}

namespace my {
    class MyDate;
}

class Vertraege;

class IRendite {
public:
    virtual void setRenditeOhneAfA( float rendite ) = 0;
    virtual void setRenditeMitAfA( float rendite ) = 0;
};

class MainWindow : public flx::Flx_Window, public IRendite {
public:
    my::Signal<IRendite, CalculationData> signalCalculateRendite;
    my::Signal<MainWindow, Vertrag> signalSaveVertrag;
public:
    MainWindow( int x, int y );
    virtual ~MainWindow();
    virtual void setRenditeOhneAfA( float rendite );
    virtual void setRenditeMitAfA( float rendite );
    void setVertraege( Vertraege &vertraege );
    Vertraege &getVertraege() const;
    void setDepotWert( DepotWert depotWert );
    void clear();
private:
    void onBtnRenditePushed( flx::Flx_Button &, flx::ActionParm & );
    void onBtnSavePushed( flx::Flx_Button &, flx::ActionParm & );
    void onNumericInputChanged( flx::Flx_NumericInput &, flx::ActionParm & );
    void onAlphaInputChanged( flx::Flx_Input &, flx::ActionParm & );
    void onMietbeginnChanged( flx::Flx_DateChooser &, my::MyDate & );
    flx::Flx_Group &createTopGroup();
    flx::Flx_Group & createContainerGroup( int x, int y, int w, int h );
    flx::Flx_Group &createCalculationGroup( int x, int y, int w, int h );
    flx::Flx_Group &createVertragGroup( int x, int y, int w, int h );
    flx::Flx_Group &createBottomGroup( int x, int y, int w, int h );
    Fl_Widget *createInput( int x, int y, int w, int kindInput, const char *lbl );
    int getTextLen( const char * ) const;
    void adjustX( int nWidgets, int left, ... );
    bool canSave() const;
    void checkSaveButton();
//    void computeMietende( const my::MyDate &, my::MyDate & );
private:
    int _yspacing, _xspacing;
    int _statusbarHeight, _toolbarHeight, _inputHeight;
    flx::Flx_ToolBar *_pToolBar;
    flx::Flx_Group *_pStatusBar;
    flx::Flx_FloatInput *_pEinzelpreis;
    flx::Flx_IntInput *_pMenge;
    flx::Flx_Output *_pGesamtpreis;
    flx::Flx_FloatInput *_pMieteContTag;
   
    flx::Flx_IntInput *_pLaufzeit;
    flx::Flx_FloatInput *_pRueckkauf;
    
    flx::Flx_FloatInput *_pAfa;
    flx::Flx_FloatInput *_pSteuersatz;
    
    flx::Flx_Output *_pRenditeMit;
    flx::Flx_Output *_pRenditeOhne;
    
    flx::Flx_Button *_pBtnRendite;
    
    flx::Flx_Input *_pAngebot;
    flx::Flx_Input *_pVertrag;
    flx::Flx_Input *_pKunde;
    flx::Flx_IntInput *_pLfdNr;
    
    flx::Flx_DateChooser *_pMietbeginn;
    flx::Flx_Output *_pMietende;
    flx::Flx_IntInput *_pAnzahl;
    
    flx::Flx_Button *_pBtnSave;
    
    flx::Flx_Table *_pTable;
    flx::Flx_Output *_pDepotZeitwert;
    flx::Flx_Output *_pDepotSummeRueckkauf;
};

#endif	/* MAINWINDOW_H */

