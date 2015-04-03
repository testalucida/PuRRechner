/* 
 * File:   Application.cpp
 * Author: max
 * 
 * Created on 20. April 2014, 23:28
 */

#include "Application.h"
#include "MainWindow.h"
#include "ContainerIO.h"
#include "DepotDataCalculator.h"

#include <FL/Fl.H>

Application::Application( ) {
    Fl::scheme( "GTK+" );
    _pWin = new MainWindow( 100, 20 );
    
    _pWin->signalCalculateRendite.
        connect< Calculator, &Calculator::onCalculate >( &_calc );
    
    _saveHandler.setVertraege( _vertraegeTableData );
    
    _pWin->signalSaveVertrag.
        connect< SaveHandler, &SaveHandler::saveVertrag >( &_saveHandler );
    
    _veranlCalc.setVertraege( _vertraegeTableData );
    
    _pWin->signalRefreshVeranlagung
            .connect< VeranlagungCalculator, 
                     &VeranlagungCalculator::onRefreshVeranlagung >( &_veranlCalc );
    
//    _pWin->signalRefreshMietertrag
//            .connect< Application, &Application::onRefreshMietertrag >( this );
}

void Application::init() {
    ContainerIO io;
    io.connect();
    _pWin->setVertraege( io.getVertraege( _vertraegeTableData ) );
    DepotDataCalculator wertCalc( _vertraegeTableData.getVertraege() );
    DepotData wert = wertCalc.getDepotData();
    _pWin->setSteuersatz( 30 );
    _pWin->setDepotData( wert );
    std::vector<int> jahre( {2014, 2015, 2016, 2017, 2018});
    _pWin->setVeranlagungsjahre( jahre );
    
}

MainWindow &Application::getWindow() const {
    return *_pWin;
}

//void Application::onRefreshMietertrag( MainWindow &, float &steuersatz ) {
//    DepotDataCalculator wertCalc( _vertraegeTableData.getVertraege() );
//    int mietertrag = wertCalc.getJahresErtragVorSteuern();
//    _pWin->setJahresMietertrag( mietertrag );
//}

Application::~Application( ) {
}

