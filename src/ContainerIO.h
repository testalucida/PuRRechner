/* 
 * File:   ContainerIO.h
 * Author: max
 *
 * Created on 18. April 2014, 21:34
 */

#ifndef CONTAINERIO_H
#define	CONTAINERIO_H

#include "MySql.h"
#include "Vertrag.h"
#include "WertverlustData.h"

#include <vector>

class VertraegeTableData;

class ContainerIO {
public:
    ContainerIO();
    virtual ~ContainerIO();
    
    /**
     * Verbindet mit der PundR - Datenbank
     */
    void connect();
    
    /**
     * Liest alle Verträge aus der Tabelle Container.
     * @param vertraege: Referenz auf das zu füllende
     * Vertraege-Objekt
     */
    VertraegeTableData &getVertraege( VertraegeTableData &vertraege );
  
    /**
     * Fügt einen Vertrag in die Tabelle Container ein.
     * @param vertrag: der einzufügenden Vertrag
     */
    void insertVertrag( const Vertrag &vertrag );
    
    /**
     * Selektiert einen Vertrag aus der Tabelle Container
     * @param vertrag: Vertragsnr. ("LF 123456")
     * @param lfdNr: laufende Nr. 0 == Erstvertrag, 1 == Verlängerung
     * @return shared_ptr auf den Vertrag.
     * Wurde zur Vertragsnummer kein Vertrag gefunden, wird ein leerer
     * Vertrag zurückgeliefert.
     */
    VertragPtr selectVertrag( const char *vertrag, int lfdNr );
    
    /**
     * Der zu ändernde Vertrag wird anhand Vertragsnummer und 
     * laufender Nummer identifiziert. Die übrigen Datenbankwerte
     * werden gem. vertrag geändert.
     * @param vertrag: der zu ändernde Vertrag
     */
    void updateVertrag( const Vertrag &vertrag );
    
    /**
     * Löscht einen Vertrag
     * @param vertrag Vertragskennung, z.B. "GC 12345"
     */
    void deleteVertrag( const char* vertrag );
    
    /**
     * Liefert eine Liste aller Wertverluste.
     * Ein Eintrag entspricht dem Wertverlust eines Vertrags.
     * @return 
     */
    //WertverlustVectorPtr getWertverluste();
    
private:
    MySql _mysql;
};

#endif	/* CONTAINERIO_H */

