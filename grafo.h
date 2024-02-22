#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <vector>
#include <list>
#include <memory>
#include "vertice.h"

using namespace std;

template < class T >
class Grafo
{
protected:
    vector<Vertice < T >* > vertices;
public:
    Grafo();
    ~Grafo();
    int numVertices();
    int numAristas();
    T obtenerDato(int indice);
    bool insertarVertice(T vertice);
    bool insertarArista(T vOrigen, T vDestino, double costo);
    int buscarVertice(T vertice);
    double buscarArista(T vOrigen, T vDestino);
    bool cambiarVertice(T vAntiguo, T vNuevo);
    bool cambiarArista(T vOrigen, T vDestino, double costo);
    bool eliminarVertice(T vertice);
    bool eliminarArista(T vOrigen, T vDestino);
    vector<int> cDebilmenteConectado(T vertice);
    vector<int> cFuertementeConectado(T vertice);
    vector<int> ascendientes(T vertice);
    vector<int> descendientes(T vertice);
    void recorridoPlano();
    void recorridoProfundidad(T vInicio);
    void recorridoAnchura(T vInicio);
    void recorridoEuler();
    shared_ptr<Grafo<T>> algoritmoPrim(T vInicio);
    vector<par> algoritmoDijkstra(T vInicio);
    shared_ptr<Grafo<T>> algoritmoKrustal();
    void floydWarshall(vector < vector < par > >& resultado);
private:
    vector<int> descendientes(vector<int> componentesConectados, Vertice<T>* vActual);
    bool esPuente(T vOrigen, int iDestino);
    void recorridoEuler(Vertice<T>* vActual, int vFinal, vector< vector<par> >& aVisitadas);
};

#include "grafo.hxx"

#endif
