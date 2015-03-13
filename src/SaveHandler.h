/* 
 * File:   SaveHandler.h
 * Author: max
 *
 * Created on 9. Februar 2015, 21:54
 */

#ifndef SAVEHANDLER_H
#define	SAVEHANDLER_H

class MainWindow;
class Vertrag;
class VertraegeTableData;

class SaveHandler {
public:
    SaveHandler();
    
    void setVertraege( VertraegeTableData & );
    void saveVertrag( MainWindow &, Vertrag & );

    virtual ~SaveHandler();
private:
    VertraegeTableData *_pVertraege;
};

#endif	/* SAVEHANDLER_H */

