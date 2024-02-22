#include <iostream>
#include "grafo.h"
#include "espacio.h"

using namespace std;

void crearTablero(Grafo<Espacio>* tablero)
{
    for (int i = 0; i < 9; i++)
    {
        Espacio espacio;
        espacio.numEspacio = i;
        espacio.caracter = '_';
        tablero->insertarVertice(espacio);
    }
    for (int i = 0; i < 9; i++)
    {
        if ((i%3)== 0)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+1), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+2), 1);
        }
        if ((i%3)== 1)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-1), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+1), 1);
        }
        if ((i%3)== 2)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-1), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-2), 1);
        }
        if (i < 3)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+3), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+6), 1);
        }
        if (i>=3 && i<6)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-3), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+3), 1);
        }
        if (i >= 6)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-3), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-6), 1);
        }
        if (i == 0)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+4), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+8), 1);
        }
        if (i == 2)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+2), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+4), 1);
        }
        if (i == 4)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-4), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-2), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+2), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+4), 1);
        }
        if (i == 6)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-2), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-4), 1);
        }
        if (i == 8)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-4), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-8), 1);
        }
    }
}

void imprimirTablero(Grafo<Espacio>* tablero)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << tablero->obtenerDato(j + (3*i)) << " ";
        }
        cout << endl;
    }
}

void alterarAristas (Grafo<Espacio>* tablero, int indice, double cambio)
{
    for (int j = 0; j < 9; j++)
    {
        double antCosto = tablero->buscarArista(tablero->obtenerDato(indice), tablero->obtenerDato(j));
        if (antCosto != 0)
        {
            tablero->cambiarArista(tablero->obtenerDato(indice), tablero->obtenerDato(j), antCosto + cambio);
            tablero->cambiarArista(tablero->obtenerDato(j), tablero->obtenerDato(indice), antCosto + cambio);
        }
    }
}

void turnoMaquinaMin(Grafo<Espacio>* tablero, int indiceX, int sumaHeuristica)
{
    for (int i = 0; i < 9; i++)
    {
        if (tablero->obtenerDato(i).caracter == '_')
        {
            alterarAristas(tablero, i, -4);
            int sumaHeuristica = 0;
            for (int j = 0; j < 9; j++)
            {
                if (tablero->obtenerDato(j).caracter == '_' || tablero->obtenerDato(j).caracter == 'O')
                    sumaHeuristica += tablero->buscarArista(tablero->obtenerDato(i), tablero->obtenerDato(j));
            }
            alterarAristas(tablero, i, 4);
        }
    }
}

void turnoMaquinaMax(Grafo<Espacio>* tablero)
{
    int maximo = -999;
    int indiceMejor = 1;
    for (int i = 0; i < 9; i++)
    {
        if (tablero->obtenerDato(i).caracter == '_')
        {
            alterarAristas(tablero, i, 1);
            int sumaHeuristica = 0;
            for (int j = 0; j < 9; j++)
            {
                if (tablero->obtenerDato(j).caracter == '_' || tablero->obtenerDato(j).caracter == 'X')
                    sumaHeuristica += tablero->buscarArista(tablero->obtenerDato(i), tablero->obtenerDato(j));
            }

            if (sumaHeuristica > maximo)
            {
                maximo = sumaHeuristica;
                indiceMejor = i;
            }
            alterarAristas(tablero, i, -1);
        }
    }
    while (true)
    {
        if (tablero->obtenerDato(indiceMejor).caracter == '_')
        {
            Espacio aux;
            aux.numEspacio = indiceMejor;
            aux.caracter = 'X';
            tablero->cambiarVertice(tablero->obtenerDato(indiceMejor), aux);
            alterarAristas(tablero, indiceMejor, 1);
            break;
        }
        else
            indiceMejor++;
    }
}

void turnoJugador(Grafo<Espacio>* tablero)
{
    int valor = 0;
    cout << "\nTu turno!! Escribe un numero de 1 a 9 para poner tu O" << endl;
    cin >> valor;
    Espacio aux;
    aux.caracter = 'O';
    aux.numEspacio = valor-1;
    tablero->cambiarVertice(tablero->obtenerDato(valor-1), aux);
    alterarAristas(tablero, valor-1, -4);
}

int main()
{
    Grafo<Espacio>* tablero = new Grafo<Espacio>();
    bool acabo = false;
    crearTablero(tablero);
    imprimirTablero(tablero);
    cout << "\nBienvenido al triqui! Juguemos. Yo sere las X y tu las O. Yo empiezo!" << endl;
    while (!acabo)
    {
        turnoMaquinaMax(tablero);
        imprimirTablero(tablero);
        turnoJugador(tablero);
    }
    delete tablero;
    return 0;
}
