/* 
 * File:   Veranlagungsdaten.h
 * Author: max
 *
 * Created on 15. März 2015, 10:38
 */

#ifndef VERANLAGUNGSDATEN_H
#define	VERANLAGUNGSDATEN_H

#include <my/TableData.h>

#include <memory>

static const char *VeranlagungsdatenHeaderNames[] = 
{ 
    "Vertrag",
    "Miete",
    "AfA(%)",
    "AfA(€)",
    "Rueckkauf", /*Jahr */
    "Veraeuß.gewinn",
    "st.Ergebnis",
    "Steuer(€)",
    NULL
};

enum VeranlagungsdatenHeaderNamesIndexes {
    VERANLAGG_VERTRAG,
    VERANLAGG_MIETE,
    VERANLAGG_AFA_PROZ,
    VERANLAGG_AFA_EURO,
    VERANLAGG_RUECKKAUF,
    VERANLAGG_VERAEUSSGEWINN,
    VERANLAGG_STEUERL_ERGEBNIS,
    VERANLAGG_STEUER
};

class VeranlagungTableData : public my::TableData {
public:
    VeranlagungTableData();
    void setValue( const char *pVal, int row, const char *pColumnName );
    virtual ~VeranlagungTableData();
private:
    
};

typedef std::shared_ptr<VeranlagungTableData> VeranlagungTableDataPtr;

#endif	/* VERANLAGUNGSDATEN_H */

