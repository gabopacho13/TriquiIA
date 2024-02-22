#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include "grafo.h"

using namespace std;

template < class T >
Grafo<T>::Grafo()
{
    this->vertices.clear();
}

template < class T >
Grafo<T>::~Grafo()
{
    for(int i=0; i<vertices.size(); i++)
    {
        if(vertices[i]!=NULL)
        {
            delete vertices[i];
        }
    }
    vertices.clear();
}

template < class T >
int Grafo<T>::numVertices()
{
    return this->vertices.size();
}

template < class T >
int Grafo<T>::numAristas()
{
    int numAristas=0;
    for(int i=0; i<vertices.size(); i++)
    {
        numAristas += vertices[i]->numAristas();
    }
    return numAristas;
}

template < class T >
bool Grafo<T>::insertarVertice(T vertice)
{
    if (this->buscarVertice(vertice) != -1){
        return false;
    }
    this->vertices.push_back(new Vertice <T>(vertice));
    return true;
}

template < class T >
bool Grafo<T>::insertarArista(T vOrigen, T vDestino, double costo)
{
    int indiceOrigen = this->buscarVertice(vOrigen);
    int indiceDestino = this->buscarVertice(vDestino);
    if (indiceOrigen == -1 || indiceDestino == -1)
    {
        return false;
    }
    return vertices[indiceOrigen]->insertarArista(indiceDestino,costo);
}

template < class T >
T Grafo<T>::obtenerDato(int indice){
    return this->vertices[indice]->obtenerDato();
}

template < class T >
int Grafo<T>::buscarVertice(T vertice)
{
    for (int i = 0; i < this->vertices.size(); i++)
    {
        if (this->vertices[i]->obtenerDato() == vertice){
            return i;
        }
    }
    return -1;
}

template < class T >
double Grafo<T>::buscarArista(T vOrigen, T vDestino)
{
    int indiceOrigen = this->buscarVertice(vOrigen);
    int indiceDestino = this->buscarVertice(vDestino);
    if (indiceOrigen == -1 || indiceDestino == -1)
        return 0;
    return this->vertices[indiceOrigen]->buscarArista(indiceDestino);
}

template < class T >
bool Grafo<T>::cambiarVertice(T vAntiguo, T vNuevo){
    for (int i = 0; i < vertices.size(); i++){
        if (vertices[i]->obtenerDato() == vAntiguo){
            vertices[i]->cambiarDato(vNuevo);
            return true;
        }
    }
    return false;
}

template < class T >
bool Grafo<T>::cambiarArista(T vOrigen, T vDestino, double costo){
    if (eliminarArista(vOrigen, vDestino)){
        insertarArista(vOrigen, vDestino, costo);
        return true;
    }
    else
        return false;
}

template < class T >
bool Grafo<T>::eliminarVertice(T vertice)
{
    int indiceVertice = this->buscarVertice(vertice);
    if (indiceVertice == -1)
        return false;
    delete vertices[indiceVertice];
    this->vertices.erase(vertices.begin() + indiceVertice);
    return true;
}

template < class T >
bool Grafo<T>::eliminarArista(T vOrigen, T vDestino)
{
    int indiceOrigen = this->buscarVertice(vOrigen);
    int indiceDestino = this->buscarVertice(vDestino);
    if (indiceOrigen == -1 || indiceDestino == -1)
        return false;
    return vertices[indiceOrigen]->eliminarArista(indiceDestino);
}

template < class T >
vector<int> Grafo<T>::cDebilmenteConectado(T vertice){
    vector<int> cDebilmenteConectado;
    int iVertice = this->buscarVertice(vertice);
    if (iVertice == -1)
	return cDebilmenteConectado;
    cDebilmenteConectado.push_back(iVertice);
    vector<int> descendientes = this->descendientes(vertice);
    vector<int> ascendientes = this->ascendientes(vertice);
    for (int i = 0; i < descendientes.size(); i++){
	if (descendientes[i] == iVertice)
	    continue;
	cDebilmenteConectado.push_back(descendientes[i]);
    }
    for (int i = 0; i < ascendientes.size(); i++){
	if (ascendientes[i] == iVertice)
	    continue;
	cDebilmenteConectado.push_back(ascendientes[i]);
    }
    return cDebilmenteConectado;
}

template < class T >
vector<int> Grafo<T>::cFuertementeConectado(T vertice){
    vector<int> cFuertementeConectado;
    if (this->buscarVertice(vertice) == -1)
	return cFuertementeConectado;
    vector<int> descendientes = this->descendientes(vertice);
    vector<int> ascendientes = this->ascendientes(vertice);
    for (int i = 0; i < descendientes.size(); i++){
	for (int j = 0; j < ascendientes.size(); j++){
	    if (descendientes[i] == ascendientes[j]){
		cFuertementeConectado.push_back(descendientes[i]);
		break;
	    }
	}
    }
    return cFuertementeConectado;
}

template < class T >
bool Grafo<T>::esPuente(T vOrigen, int iDestino){
    bool esPuente = true;
    vector<int> cFuertementeConectado = this->cFuertementeConectado(vOrigen);
    for (int i = 0; i < cFuertementeConectado.size(); i++){
	if (cFuertementeConectado[i] == iDestino){
	    esPuente = false;
	    break;
	}
    }
    return esPuente;
}

template < class T >
vector<int> Grafo<T>::ascendientes(T vertice){
    vector<int> ascendientes;
    int indiceVertice = this->buscarVertice(vertice);
    if (indiceVertice == -1)
	return ascendientes;
    for (int i = 0; i < this->vertices.size(); i++){
	if (i == indiceVertice){
	    ascendientes.push_back(indiceVertice);
	    continue;
	}
	T nVertice = this->obtenerDato(i);
	vector<int> descendientes = this->descendientes(nVertice);
	for (int j = 0; j < descendientes.size(); j++){
	    if (descendientes[j] == indiceVertice){
		ascendientes.push_back(i);
		break;
	    }
	}
    }
    return ascendientes;
}

template < class T>
vector<int> Grafo<T>::descendientes(T vertice){
    int indice = this->buscarVertice(vertice);
    vector<int> conectados;
    if (indice == -1)
	return conectados;
    conectados.push_back(indice);
    return this->descendientes(conectados, this->vertices[indice]);
}

template < class T>
vector<int> Grafo<T>::descendientes(vector<int> conectados, Vertice<T>* vActual){
    vector<par> aristas = vActual->obtenerAristas();
    for (int i = 0; i < aristas.size(); i++) {
	bool insertado = false;
	for (int j = 0; j < conectados.size(); j++){
	    if (conectados[j] == aristas[i].indice){
		insertado = true;
		break;
	    }
	}
	if (!insertado){
	    conectados.push_back(aristas[i].indice);
	    conectados = this->descendientes(conectados, this->vertices[aristas[i].indice]);
	}
    }
    return conectados;
}

template < class T >
void Grafo<T>::recorridoPlano()
{
    for (int i = 0; i < vertices.size(); i++)
        cout << vertices[i]->obtenerDato() << " ";
    cout << endl;
}

template < class T >
void Grafo<T>::recorridoProfundidad(T vInicio)
{
    vector<int> visitados;
    stack<Vertice<T>*> pVertices;
    int indice = this->buscarVertice(vInicio);
    if (indice != -1)
        pVertices.push(this->vertices[indice]);
    while (!pVertices.empty())
    {
        bool visitado = false;
        int indice = this->buscarVertice(pVertices.top()->obtenerDato());
        for (int i = 0; i < visitados.size(); i++)
        {
            if (indice == visitados[i])
            {
                visitado = true;
                break;
            }
        }
        if (!visitado)
        {
            cout << pVertices.top()->obtenerDato() << " ";
            visitados.push_back(indice);
            pVertices.pop();
            vector<par> aristasVertice = this->vertices[indice]->obtenerAristas();
            for (int i = 0; i < aristasVertice.size(); i++)
            {
                pVertices.push(this->vertices[aristasVertice[i].indice]);
            }
        }
        else
            pVertices.pop();
    }
    cout << endl;
}

template < class T >
void Grafo<T>::recorridoAnchura(T vInicio)
{
    vector<int> visitados;
    queue<Vertice<T>*> pVertices;
    int indice = this->buscarVertice(vInicio);
    if (indice != -1)
        pVertices.push(this->vertices[indice]);
    while (!pVertices.empty())
    {
        bool visitado = false;
        indice = this->buscarVertice(pVertices.front()->obtenerDato());
        for (int i = 0; i < visitados.size(); i++)
        {
            if (indice == visitados[i])
            {
                visitado = true;
                break;
            }
        }
        if (!visitado)
        {
            cout << pVertices.front()->obtenerDato() << " ";
            visitados.push_back(indice);
            pVertices.pop();
            vector<par> aristasVertice = this->vertices[indice]->obtenerAristas();
            for (int i = 0; i < aristasVertice.size(); i++)
            {
                pVertices.push(this->vertices[aristasVertice[i].indice]);
            }
        }
        else
            pVertices.pop();
    }
    cout << endl;
}

template < class T >
void Grafo<T>::recorridoEuler(){
    bool existe = true;
    int iSalidaExtra = -1;
    int iEntradaExtra = -1;
    try{
	for (int i = 0; i < this->vertices.size(); i++){
	    int numSalidas = this->vertices[i]->numAristas();
	    int numEntradas = 0;
	    for (int j = 0; j < this->vertices.size(); j++){
		if (this->vertices[j]->buscarArista(i) != 0){
		    numEntradas++;
		}
	    }
	    if (numEntradas != numSalidas){
		if (abs(numEntradas - numSalidas) == 1){
		    if (numEntradas > numSalidas){
			if (iEntradaExtra == -1)
			    iEntradaExtra = i;
			else
			    throw runtime_error("No existe un camino de Euler para este grafo");
		    }
		    else{
			if (iSalidaExtra == -1)
			    iSalidaExtra = i;
			else
			    throw runtime_error("No existe un camino de Euler para este grafo");
		    }
		}
		else
		    throw runtime_error("No existe un camino de Euler para este grafo");
	    }
	}
	vector< vector<par> > aVisitadas;
	for (int i = 0; i < this->vertices.size(); i++){
	    vector<par> nVector;
	    aVisitadas.push_back(nVector);
	}
	if (iSalidaExtra == -1)
	    this->recorridoEuler(this->vertices[0], 0, aVisitadas);
	else
	    this->recorridoEuler(this->vertices[iSalidaExtra], iEntradaExtra, aVisitadas);
	cout << endl;
    }
    catch (const exception& e){
	cout << e.what() << endl;
    }
}

template < class T >
void Grafo<T>::recorridoEuler(Vertice<T>* vActual, int vFinal, vector< vector<par> >& aVisitadas){
    cout << vActual->obtenerDato() << " ";
    vector<par> aVertice = vActual->obtenerAristas();
    int iActual = this->buscarVertice(vActual->obtenerDato());
    par posibleSiguiente;
    posibleSiguiente.indice = -1;
    for (int i = 0; i < aVertice.size(); i++){
	bool visitada = false;
	for (int j = 0; j < aVisitadas[iActual].size(); j++){
	    if (aVertice[i] == aVisitadas[iActual][j]){
		visitada = true;
		break;
	    }
	}
	if (!visitada){
	    if (this->esPuente(vActual->obtenerDato(), aVertice[i].indice))
		posibleSiguiente = aVertice[i];
	    else if (posibleSiguiente.indice == -1 && aVertice[i].indice == vFinal){
		posibleSiguiente = aVertice[i];
	    }
	    else{
		posibleSiguiente.indice = -1;
		aVisitadas[iActual].push_back(aVertice[i]);
		this->recorridoEuler(this->vertices[aVertice[i].indice], vFinal, aVisitadas);
		break;
	    }
	}
    }
    if (posibleSiguiente.indice != -1){
	aVisitadas[iActual].push_back(posibleSiguiente);
	this->recorridoEuler(this->vertices[posibleSiguiente.indice], vFinal, aVisitadas);
    }
}

template < class T >
shared_ptr<Grafo<T>> Grafo<T>::algoritmoPrim(T vInicio) {
    vector<int> vVisitados;
    vector<par> aVisitadas;
    shared_ptr<Grafo<T>> resultadoPrim = make_shared<Grafo<T>>();
    vector<T> descendientes = this->descendientes(vInicio);
    int indiceInicio = this->buscarVertice(vInicio);
    if (indiceInicio != -1){
	resultadoPrim->insertarVertice(vInicio);
	vVisitados.push_back(indiceInicio);
    }
    while (vVisitados.size() != descendientes.size()) {
	T padreVertice;
	T nuevoVertice;
	par nuevaArista;
	int costoMenor = 9999;
	for (int i = 0; i < vVisitados.size(); i++) {
	    vector<par> aristasVertice = this->vertices[vVisitados[i]]->obtenerAristas();
	    for (int j = 0; j < aristasVertice.size(); j++){
		bool repetido = false;
		for (int k = 0; k < aVisitadas.size(); k++) {
		    if (aristasVertice[j] == aVisitadas[k]){
			repetido = true;
			break;
		    }
		}
		if (!repetido && aristasVertice[j].costo < costoMenor){
		    padreVertice = this->vertices[vVisitados[i]]->obtenerDato();
		    nuevoVertice = this->vertices[aristasVertice[j].indice]->obtenerDato();
		    nuevaArista = aristasVertice[j];
		    costoMenor = nuevaArista.costo;
		}
	    }
	}
	resultadoPrim->insertarVertice(nuevoVertice);
	resultadoPrim->insertarArista(padreVertice, nuevoVertice, costoMenor);
	vVisitados.push_back(this->buscarVertice(nuevoVertice));
	aVisitadas.push_back(nuevaArista);
    }
    return resultadoPrim;
}

template < class T >
vector<par> Grafo<T>::algoritmoDijkstra(T vInicio) {
    vector<par> resultados;
    vector<int> visitados;
    deque<int> porVisitar;
    if (this->buscarVertice(vInicio) == -1)
	return resultados;
    for (int i = 0; i < this->vertices.size(); i++) {
	par nPar;
	if (this->vertices[i]->obtenerDato() == vInicio)
	    nPar.costo=0;
	else
	    nPar.costo=9999;
	porVisitar.push_back(i);
	nPar.indice=i;
	resultados.push_back(nPar);
    }
    while (!porVisitar.empty()) {
	int proxVisitar = 0;
	int costoMenor = 9999;
	int posEliminar = 0;
	for (int i = 0; i < resultados.size(); i++){
	    if (resultados[i].costo < costoMenor){
		for (int j = 0; j < porVisitar.size(); j++) {
		    if (porVisitar[j] == i) {
			costoMenor = resultados[i].costo;
			proxVisitar = porVisitar[j];
			posEliminar = j;
		    }
		}
	    }
	}
	visitados.push_back(proxVisitar);
	porVisitar.erase(porVisitar.begin() + posEliminar);
	vector<par> aristasVertice = this->vertices[proxVisitar]->obtenerAristas();
	for (int i = 0; i < aristasVertice.size(); i++) {
	    int costoRuta = resultados[proxVisitar].costo + aristasVertice[i].costo;
	    if (costoRuta < resultados[aristasVertice[i].indice].costo) {
		resultados[aristasVertice[i].indice].costo = costoRuta;
		resultados[aristasVertice[i].indice].indice = proxVisitar;
	    }
	}
    }
    return resultados;
}

template< class T >
shared_ptr<Grafo<T>> Grafo<T>::algoritmoKrustal(){
    vector <vector<par> > aristas;
    for (int i = 0; i < vertices.size(); i++){
	vector<par> nVector;
	aristas.push_back(nVector);
	vector<par> aVertice = this->vertices[i]->obtenerAristas();
	for (int j = 0; j < aVertice.size(); j++){
	    aristas[i].push_back(aVertice[j]);
	}
    }
    shared_ptr<Grafo<T>> resultado = make_shared<Grafo<T>>();
    while (!aristas.empty()){
	double menorCosto = 9999;
	int iOrigen = -1;
	int iDestino = -1;
	int iBorrar = -1;
	bool esArbolDiferente = true;
	bool estaVacia = true;
	for (int i = 0; i < aristas.size(); i++){
	    for (int j = 0; j < aristas[i].size(); j++){
		if (aristas[i][j].costo < menorCosto){
		    menorCosto = aristas[i][j].costo;
		    iOrigen = i;
		    iDestino = aristas[i][j].indice;
		    iBorrar = j;
		}
	    }
	}
	aristas[iOrigen].erase(aristas[iOrigen].begin() + iBorrar);
	for (int i = 0; i < aristas.size(); i++){
	    if (!aristas[i].empty()){
		estaVacia = false;
		break;
	    }
	}
	if (estaVacia){
	    aristas.clear();
	}
	vector<int> cDebilmenteConectado = resultado->cDebilmenteConectado(this->vertices[iOrigen]->obtenerDato());
	for (int i = 0; i < cDebilmenteConectado.size(); i++){
	    if (cDebilmenteConectado[i] == iDestino){
		esArbolDiferente = false;
		break;
	    }
	}
	if (esArbolDiferente){
	    resultado->insertarVertice(this->vertices[iOrigen]->obtenerDato());
	    resultado->insertarVertice(this->vertices[iDestino]->obtenerDato());
	    resultado->insertarArista(this->vertices[iOrigen]->obtenerDato(), this->vertices[iDestino]->obtenerDato(), menorCosto);
	}
    }
    return resultado;
}

template < class T >
void Grafo<T>::floydWarshall(vector < vector <par> > &resultado){
    for (int i = 0; i < this->vertices.size(); i++) {
	par nPar;
	nPar.indice = -1;
	nPar.costo = 9999;
	vector<par> nResultado(this->vertices.size(), nPar);
	resultado.push_back(nResultado);
	resultado[i][i].costo = 0;
    }
    for (int i = 0; i < this->vertices.size(); i++){
	vector <par> aristas = this->vertices[i]->obtenerAristas();
	for (int j = 0; j <aristas.size(); j++){
		resultado[i][aristas[j].indice].costo = aristas[j].costo;
		resultado[i][aristas[j].indice].indice = i;
	}
    }
    for(int k=0;k<this->vertices.size();k++){
	for(int i=0;i<this->vertices.size();i++){
	   if (i == k)
		continue;
           for(int j=0; j<resultado[i].size(); j++){
		if (i == j || j == k){
		    continue;
		}
		if (resultado[i][k].costo != 9999 && resultado[k][j].costo != 9999 && resultado[i][k].costo + resultado[k][j].costo < resultado[i][j].costo){
		    resultado[i][j].costo = resultado[i][k].costo + resultado[k][j].costo;
		    resultado[i][j].indice = k;
		}
           }
       }
   }
}
