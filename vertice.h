#ifndef __VERTICE_H__
#define __VERTICE_H__

#include <vector>
#include <list>
#include "par.h"

using namespace std;


template < class T >
class Vertice
{

protected:
    T dato;
    vector <par> aristas;
public:
    Vertice();
    Vertice(T dato);
    ~Vertice();
    T obtenerDato();
    void cambiarDato(T vNuevo);
    vector<par> obtenerAristas();
    int numAristas();
    bool insertarArista(int indiceDestino, double costo);
    int buscarArista(int indiceDestino);
    bool eliminarArista(int indiceDestino);
};

#include "vertice.hxx"

#endif
