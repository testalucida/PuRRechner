/* 
 * File:   Vertrag.h
 * Author: max
 *
 * Created on 8. Februar 2015, 14:36
 */

#ifndef VERTRAG_H
#define	VERTRAG_H

#include <my/CharBuffer.h>
#include <my/datetime.h>

#include <memory>

using namespace my;


struct Vertrag {
    CharBuffer Kunde;
    CharBuffer Angebot;
    CharBuffer Vertrag;
    int LfdNr;
    float Einzelpreis;
    int Menge;
    float Gesamtpreis;
    float Tagesmiete;
    int JahreMietdauer;
    float Rueckkaufswert;
    float AfA;
    MyDate Mietbeginn;
    MyDate Mietende;
    bool isEmpty() { return Kunde.getLength() == 0; }
};

typedef shared_ptr<Vertrag> VertragPtr;

#endif	/* VERTRAG_H */

