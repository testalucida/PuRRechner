/* 
 * File:   VertragProvider.h
 * Author: max
 *
 * Created on 4. April 2015, 19:47
 */

#ifndef VERTRAGPROVIDER_H
#define	VERTRAGPROVIDER_H

#include "ContainerIO.h"

class VertraegeTableData;

class VertragProvider {
public:
    static VertragProvider &instance();
    
    /**
     * selektiert alle Verträge aus der Datenbank und
     * errechnet für jeden Vertrag den Veräußerungsgewinn
     * @param 
     * @return  ein TableData-Objekt mit allen Verträgen
     */
    VertraegeTableData &getVertraege( VertraegeTableData & );
private:
    VertragProvider();
    static void destroy();
public:   
    ~VertragProvider();
private:
    static VertragProvider *_pThis;
    ContainerIO _containerIO;
};

#endif	/* VERTRAGPROVIDER_H */

