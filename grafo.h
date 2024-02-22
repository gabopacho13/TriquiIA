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
    vector<int> cDebilmenteConectado(T vertice); //Funcion no utilizada
    vector<int> cFuertementeConectado(T vertice); //Funcion no utilizada
    vector<int> ascendientes(T vertice); //Funcion no utilizada
    vector<int> descendientes(T vertice); //Funcion no utilizada
    void recorridoPlano(); //Funcion no utilizada
    void recorridoProfundidad(T vInicio); //Funcion no utilizada
    void recorridoAnchura(T vInicio); //Funcion no utilizada
    void recorridoEuler(); //Funcion no utilizada
    shared_ptr<Grafo<T>> algoritmoPrim(T vInicio); //Funcion no utilizada
    vector<par> algoritmoDijkstra(T vInicio); //Funcion no utilizada
    shared_ptr<Grafo<T>> algoritmoKrustal(); //Funcion no utilizada
    void floydWarshall(vector < vector < par > >& resultado); //Funcion no utilizada
private:
    vector<int> descendientes(vector<int> componentesConectados, Vertice<T>* vActual); //Funcion no utilizada
    bool esPuente(T vOrigen, int iDestino); //Funcion no utilizada
    void recorridoEuler(Vertice<T>* vActual, int vFinal, vector< vector<par> >& aVisitadas); //Funcion no utilizada
};

#include "grafo.hxx"

#endif
