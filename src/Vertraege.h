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
    VertragPtrVectorPtr getVertraege() ;

    virtual ~VertraegeTableData();
private:
    void buildHeaderIndexMapper();
    VertragPtr createVertragFromRow( int row ) const;
    int getColumnIndex( const char *pHeader ) const;
private:
    std::map<std::string, int> _headerIndexMapper;
};

#endif	/* VERTRAEGE_H */

