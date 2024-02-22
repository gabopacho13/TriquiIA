#ifndef __ESPACIO_H__
#define __ESPACIO_H__

using namespace std;

typedef struct Espacio{
    int numEspacio;
    char caracter;

    Espacio& operator = (const Espacio &e)
    {
        numEspacio = e.numEspacio;
        caracter = e.caracter;
        return *this;
    }

    bool operator == (const Espacio &e) const
    {
        return (numEspacio == e.numEspacio);
    }

    friend ostream& operator << (ostream &o, const Espacio &e)
    {
        o << e.caracter;
        return o;
    }
};

#endif
