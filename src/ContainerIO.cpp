/* 
 * File:   ContainerIO.cpp
 * Author: max
 * 
 * Created on 18. April 2014, 21:34
 */

#include "ContainerIO.h"
#include "Vertraege.h"
#include "password.h"


#include <my/CharBuffer.h>
#include <my/TableData.h>

using namespace my;

ContainerIO::ContainerIO( ) {
}

void ContainerIO::connect() {
    _mysql.connect( "root", "PundR", password );
}

VertraegeTableData &ContainerIO::getVertraege( VertraegeTableData& vertraege ) {
    CharBuffer sql( "select vertrag, lfdnr, angebot, kunde, einzelpreis, menge, einzelpreis * menge as gesamtpreis " );
    //                        0        1       2      3        4           5                                6
    sql.add( ", tagesmiete, jahremietdauer, mietbeginn, mietende, rueckkauf, rueckkauf * menge as gesamtrueckkauf " );
    //             7             8             9           10       11                                   12                 
    sql.add( ", rueckkauf*menge - ((menge*einzelpreis*afa*jahremietdauer)/100) as veraeussgewinn, afa " );
    //                                                                                13          14
    sql.add( "from Container order by mietende desc, vertrag, lfdnr" );
    
    _mysql.select( sql.get(), vertraege );
    
    return vertraege;
}

void ContainerIO::insertVertrag( const Vertrag &vertrag ) {
    
    CharBuffer sql( "insert into Container " );
    sql.add( "( vertrag, lfdnr, angebot, kunde, einzelpreis, menge, tagesmiete " )
       .add( ", jahremietdauer, mietbeginn, mietende, rueckkauf, afa ) " )
       .add( "values( ':ve', :lf, ':an', ':kd', :ep, :mng, :tm " )
       .add( ", :j, ':mb', ':me', :r, :afa ) " );
    
    sql.replace( ":ve", vertrag.Vertrag.get() );
    sql.replace( ":lf", std::to_string( vertrag.LfdNr ).c_str() );
    sql.replace( ":an", vertrag.Angebot.get() );
    sql.replace( ":kd", vertrag.Kunde.get() );
    sql.replace( ":ep", std::to_string( vertrag.Einzelpreis ).c_str() );
    sql.replace( ":mng", std::to_string( vertrag.Menge ).c_str() );
    sql.replace( ":tm", std::to_string( vertrag.Tagesmiete ).c_str() );
    sql.replace( ":j", std::to_string( vertrag.JahreMietdauer ).c_str() );
    sql.replace( ":mb", vertrag.Mietbeginn.ToIsoString().c_str() );
    sql.replace( ":me", vertrag.Mietende.ToIsoString().c_str() );
    sql.replace( ":r", std::to_string( vertrag.Rueckkaufswert ).c_str() );
    sql.replace( ":afa", std::to_string( vertrag.AfA ).c_str() );
    
    _mysql.exec( sql.get() );
    
}

VertragPtr ContainerIO::selectVertrag( const char *vertrag, int lfdNr ) {
    CharBuffer sql( "select " );
    sql.add( "vertrag, lfdnr, angebot, kunde, einzelpreis, menge, tagesmiete " )
        //      0        1      2        3       4           5         6
       .add( ", jahremietdauer, mietbeginn, mietende, rueckkauf, afa ") 
        //             7            8          9          10      11
       .add( "from Container " )
       .add( "where vertrag = ':ve' and lfdnr = :lf " );
    
    sql.replace( ":ve", vertrag );
    sql.replace( ":lf", std::to_string( lfdNr ).c_str() );
    
    TableData data;
    _mysql.select( sql.get(), data );
    
    VertragPtr pV( new Vertrag() );
    if( data.getRowCount() > 0 ) {
        pV->Vertrag.add( data.getValue( 0, 0 ) );
        pV->LfdNr = data.getIntValue( 0, 1 );
        pV->Angebot.add( data.getValue( 0, 2 ) );
        pV->Kunde.add( data.getValue( 0, 3 ) );
        pV->Einzelpreis = data.getFloatValue( 0, 4 );
        pV->Menge = data.getIntValue( 0, 5 );
        pV->Tagesmiete = data.getFloatValue( 0, 6 );
        pV->JahreMietdauer = data.getIntValue( 0, 7 );
        pV->Mietbeginn.FromIsoString( data.getValue( 0, 8 ) );
        pV->Mietende.FromIsoString( data.getValue( 0, 9 ) );
        pV->Rueckkaufswert = data.getFloatValue( 0, 10 );
        pV->AfA = data.getFloatValue( 0, 11 );
    }
    
    return pV; 
}

void ContainerIO::updateVertrag( const Vertrag &vertrag ) {
    CharBuffer sql( "update Container " );
    sql.add( "set " )
        .add( "angebot = ':an', " )
        .add( "kunde = ':kd', " )
        .add( "einzelpreis = :ep, ")
        .add( "menge = :mng, " )
        .add( "tagesmiete = :tm, " )
        .add( "jahremietdauer = :j, " )
        .add( "mietbeginn = ':mb', " )
        .add( "mietende = ':me', " )
        .add( "rueckkauf = :r, " )
        .add( "afa = :afa " )
        .add( "where vertrag = ':ve' and lfdnr = :lf " );
    
    sql.replace( ":ve", vertrag.Vertrag.get() );
    sql.replace( ":lf", std::to_string( vertrag.LfdNr ).c_str() );
    sql.replace( ":an", vertrag.Angebot.get() );
    sql.replace( ":kd", vertrag.Kunde.get() );
    sql.replace( ":ep", std::to_string( vertrag.Einzelpreis ).c_str() );
    sql.replace( ":mng", std::to_string( vertrag.Menge ).c_str() );
    sql.replace( ":tm", std::to_string( vertrag.Tagesmiete ).c_str() );
    sql.replace( ":j", std::to_string( vertrag.JahreMietdauer ).c_str() );
    sql.replace( ":mb", vertrag.Mietbeginn.ToIsoString().c_str() );
    sql.replace( ":me", vertrag.Mietende.ToIsoString().c_str() );
    sql.replace( ":r", std::to_string( vertrag.Rueckkaufswert ).c_str() );
    sql.replace( ":afa", std::to_string( vertrag.AfA ).c_str() );
    
    _mysql.exec( sql.get() );
}

 WertverlustVectorPtr ContainerIO::getWertverluste() {
    CharBuffer sql( "SELECT vertrag, lfdnr, mietbeginn, mietende, " );
    //                         0       1        2          3
    sql.add( "einzelpreis * menge as kaufpreis, rueckkauf * menge as rueckkauf, " )
    //                                4                              5
       .add( "((einzelpreis * menge - rueckkauf * menge)/(jahremietdauer*365)) as wertverlustprotag, " )
    //                                                                                  6
       .add( "datediff(mietende, current_date) as tagerestlaufzeit " )
    //                                                  7
       .add( "FROM Container " )
       .add( "where mietbeginn <= curdate() and mietende >= curdate()" );
       
	TableData data;
    _mysql.select( sql.get(), data );
    
     WertverlustVectorPtr pListe( new vector<WertverlustDataPtr>() );
     
     for( int r = 0, rmax = data.getRowCount(); r < rmax; r++ ) {
         
         WertverlustDataPtr pWv( new WertverlustData() );
         pWv->Vertrag.add( data.getValue( r, 0 ) );
         pWv->LfdNr = data.getIntValue( r, 1 );
         pWv->Mietbeginn.FromIsoString( data.getValue( r, 2 ) );
         pWv->Mietende.FromIsoString( data.getValue( r, 3 ) );
         pWv->Kaufpreis = data.getIntValue( r, 4 );
         pWv->Rueckkauf = data.getIntValue( r, 5 );
         pWv->WertverlustProTag = data.getFloatValue( r, 6 );
         pWv->TageRestlaufzeit = data.getIntValue( r, 7 );
         
         pListe->push_back( pWv );
     }
     
     return pListe;
 }

ContainerIO::~ContainerIO( ) {
    _mysql.disconnect();
}

