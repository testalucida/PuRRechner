/* 
 * File:   Vertraege.h
 * Author: max
 *
 * Created on 18. April 2014, 22:08
 */

#ifndef VERTRAEGE_H
#define	VERTRAEGE_H

#include "Vertrag.h"

#include <my/TableData.h>
#include <my/CharBuffer.h>

#include <vector>
#include <memory>
#include <map>

class VertraegeTableData : public my::TableData {
public:
    VertraegeTableData();

    /**
     * Macht aus jeder Zeile dieses TableData-Objekts
     * ein VertragPtr-Objekt und liefert alle Verträge
     * in einem Vector von VertragPtr-Instanzen zurück.
     * @return  VertragPtrVectorPtr
     */
    VertragPtrVectorPtr getVertraege() const;
    
    /**
     * Liefert ein VertragPtr-Objekt, das aus den Daten
     * der TableData-Row mit dem Index idx erzeugt wird.
     * @param idx Index der TableData-Row
     * @return  VertragPtr
     */
    VertragPtr getVertrag( int idx ) const;
     int getColumnIndex( const char *pHeader ) const;
     void buildHeaderIndexMapper();
     
    virtual ~VertraegeTableData();
private:
    
    VertragPtr createVertragFromRow( int row ) const;
   
private:
    std::map<std::string, int> _headerIndexMapper;
};

#endif	/* VERTRAEGE_H */

