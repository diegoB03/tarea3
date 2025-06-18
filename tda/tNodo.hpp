#ifndef __TNODO_H__
#define __TNODO_H__

typedef int tipoElem;

struct tNodoArbolBin {
    tipoElem info;
    tNodoArbolBin* izq;
    tNodoArbolBin* der;
};

#endif
