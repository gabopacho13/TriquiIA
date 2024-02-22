#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include "vertice.h"


using namespace std;




template < class T >
Vertice<T>::Vertice()
{
    aristas.clear();
}

template < class T >
Vertice<T>::Vertice(T dato)
{
    this->dato=dato;
    aristas.clear();
}

template < class T >
Vertice<T>::~Vertice()
{
    aristas.clear();
}

template < class T >
int Vertice<T>::numAristas()
{
    return aristas.size();
}

template < class T >
T Vertice<T>::obtenerDato()
{
    return dato;
}

template < class T >
void Vertice<T>::cambiarDato(T vNuevo)
{
    this->dato = vNuevo;
}

template < class T >
vector<par> Vertice<T>::obtenerAristas()
{
    return this->aristas;
}

template < class T >
bool Vertice<T>::insertarArista(int indiceDestino, double costo)
{

    for (int i = 0; i < this->aristas.size(); i++)
    {
        if (this->aristas[i].indice==indiceDestino)
            return false;
    }
    par nPar;
    nPar.indice = indiceDestino;
    nPar.costo = costo;
    this->aristas.push_back(nPar);
    return true;

}

template < class T >
int Vertice<T>::buscarArista(int indiceDestino)
{
    for (int i = 0; i < this->aristas.size(); i++)
    {
        if (this->aristas[i].indice == indiceDestino)
            return aristas[i].costo;
    }
    return 0;
}

template < class T >
bool Vertice<T>::eliminarArista(int indiceDestino)
{

    for (int i = 0; i < this->aristas.size(); i++)
    {
        if (this->aristas[i].indice == indiceDestino)
        {
            this->aristas.erase(this->aristas.begin() + i);
            return true;
        }
    }
    return false;
}

