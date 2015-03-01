/* 
 * File:   Application.cpp
 * Author: max
 * 
 * Created on 20. April 2014, 23:28
 */

#include "Application.h"
#include "MainWindow.h"
#include "ContainerIO.h"
#include "DepotWertCalculator.h"

#include <FL/Fl.H>

Application::Application( ) {
    Fl::scheme( "GTK+" );
    _pWin = new MainWindow( 100, 100 );
    
    _pWin->signalCalculateRendite.
        connect< Calculator, &Calculator::onCalculate >( &_calc );
    
    _saveHandler.setVertraege( _vertraege );
    
    _pWin->signalSaveVertrag.
        connect< SaveHandler, &SaveHandler::saveVertrag >( &_saveHandler );
}

void Application::init() {
    ContainerIO io;
    io.connect();
    _pWin->setVertraege( io.getVertraege( _vertraege ) );
    DepotWertCalculator wertCalc;
    DepotWert wert = wertCalc.getDepotWert();
    _pWin->setDepotWert( wert );
}

MainWindow &Application::getWindow() const {
    return *_pWin;
}

Application::~Application( ) {
}

