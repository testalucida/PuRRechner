/* 
 * File:   DialogModel.h
 * Author: max
 *
 * Created on 18. April 2014, 23:23
 */

#ifndef DIALOGMODEL_H
#define	DIALOGMODEL_H

#include "Vertraege.h"

class DialogModel {
public:
    DialogModel();
    virtual ~DialogModel();
    VertraegeTableData &getVertraege() const;
private:
    VertraegeTableData _vertraege;
};

#endif	/* DIALOGMODEL_H */

