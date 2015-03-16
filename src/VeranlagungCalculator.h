/* 
 * File:   VeranlagungCalculator.h
 * Author: max
 *
 * Created on 15. März 2015, 12:08
 */

#ifndef VERANLAGUNGCALCULATOR_H
#define	VERANLAGUNGCALCULATOR_H

class VertraegeTableData;
class MainWindow;
class VeranlagungParm;

namespace my {
    class MyDate;
}

class VeranlagungCalculator {
public:
    VeranlagungCalculator();
    
    void setVertraege( VertraegeTableData &vertraege ) {
        _pVertraegeTableData = &vertraege;
    }
    
    void onRefreshVeranlagung( MainWindow &, VeranlagungParm & );
    
    virtual ~VeranlagungCalculator();
private:
    int getAnzahlMiettage( 
                       const my::MyDate &mietbeginn, 
                       const my::MyDate &mietende,
                       int veranlagungsjahr ) const;
private:
    VertraegeTableData *_pVertraegeTableData;
};

#endif	/* VERANLAGUNGCALCULATOR_H */

