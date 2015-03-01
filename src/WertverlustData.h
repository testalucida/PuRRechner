/* 
 * File:   WertverlustData.h
 * Author: max
 *
 * Created on 13. Februar 2015, 19:36
 */

#ifndef WERTVERLUSTDATA_H
#define	WERTVERLUSTDATA_H

#include <my/CharBuffer.h>
#include <my/datetime.h>
#include <memory>
#include <vector>

struct WertverlustData {
    my::CharBuffer Vertrag;
    int LfdNr;
    my::MyDate Mietbeginn;
    my::MyDate Mietende;
    int Kaufpreis; //ALLER Container eines Vertrags
    int Rueckkauf; //ALLER Container eines Vertrags
    float WertverlustProTag; //ALLER Container eines Vertrag
    int TageRestlaufzeit;
};

typedef shared_ptr<WertverlustData> WertverlustDataPtr;
typedef shared_ptr<std::vector<WertverlustDataPtr> > WertverlustVectorPtr;

#endif	/* WERTVERLUSTDATA_H */

