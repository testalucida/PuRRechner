/* 
 * File:   Application.h
 * Author: max
 *
 * Created on 20. April 2014, 23:28
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include "Calculator.h"
#include "Vertraege.h"
#include "SaveHandler.h"

class MainWindow;

class Application {
public:
    Application();
    void init();
    MainWindow &getWindow() const;
    virtual ~Application();
private:
    MainWindow *_pWin;
    Calculator _calc;
    Vertraege _vertraege;
    SaveHandler _saveHandler;
};

#endif	/* APPLICATION_H */

