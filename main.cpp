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

int imprimirTablero(Grafo<Espacio>* tablero)
{
    int cont = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            char caracter = tablero->obtenerDato(j + (3*i)).caracter;
            cout << caracter << " ";
            if (caracter == '_')
                cont++;
        }
        cout << endl;
    }
    return cont;
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

void turnoMaquinaMin(Grafo<Espacio>* tablero, int indiceX, int &sumaHeuristica)
{
    int minimo = 999;
    for (int i = 0; i < 9; i++)
    {
        if (i == indiceX)
            continue;
        if (tablero->obtenerDato(i).caracter == '_')
        {
            int posMinimo = 0;
            alterarAristas(tablero, i, -4);
            for (int j = 0; j < 9; j++)
            {
                if (tablero->obtenerDato(j).caracter == '_' || tablero->obtenerDato(j).caracter == 'O')
                {
                    posMinimo += tablero->buscarArista(tablero->obtenerDato(i), tablero->obtenerDato(j));
                }
            }
            if (posMinimo < minimo)
                minimo = posMinimo;
            alterarAristas(tablero, i, 4);
        }
    }
    sumaHeuristica += minimo;
}

void turnoMaquinaMax(Grafo<Espacio>* tablero)
{
    cout << "Es mi turno!!" << endl;
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
            turnoMaquinaMin(tablero, i, sumaHeuristica);
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

char verificarGanador(Grafo<Espacio>* tablero)
{
    int contDiagDer = 0;
    int contDiagIzq = 0;
    for (int i = 0; i < 3; i++)
    {
        int contHor = 0;
        int contVert = 0;
        for (int j = 0; j < 3; j++)
        {
            if (tablero->obtenerDato(i+3*j).caracter == 'O')
                contVert--;
            if (tablero->obtenerDato(3*i+j).caracter == 'O')
                contHor--;
            if (i == j && tablero->obtenerDato(2*i+2*j).caracter == 'O')
                contDiagDer--;
            if (i == 2-j && tablero->obtenerDato(3*i+j).caracter == 'O')
                contDiagIzq--;
            if (tablero->obtenerDato(i+3*j).caracter == 'X')
                contVert++;
            if (tablero->obtenerDato(3*i+j).caracter == 'X')
                contHor++;
            if (i == j && tablero->obtenerDato(2*i+2*j).caracter == 'X')
                contDiagDer++;
            if (i == 2-j && tablero->obtenerDato(3*i+j).caracter == 'X')
                contDiagIzq++;
        }
        if (contVert == 3 || contHor == 3 || contDiagDer == 3 || contDiagIzq == 3)
            return 'X';
        if (contVert == -3 || contHor == -3 || contDiagDer == -3 || contDiagIzq == -3)
            return 'O';
        if (contVert == -2)
        {
            tablero->cambiarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+3), -40);
            tablero->cambiarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+6), -40);
            tablero->cambiarArista(tablero->obtenerDato(i+3), tablero->obtenerDato(i), -40);
            tablero->cambiarArista(tablero->obtenerDato(i+6), tablero->obtenerDato(i), -40);
        }
        if (contHor == -2)
        {
            tablero->cambiarArista(tablero->obtenerDato(3*i), tablero->obtenerDato(3*i+1), -40);
            tablero->cambiarArista(tablero->obtenerDato(3*i), tablero->obtenerDato(3*i+2), -40);
            tablero->cambiarArista(tablero->obtenerDato(3*i+1), tablero->obtenerDato(3*i), -40);
            tablero->cambiarArista(tablero->obtenerDato(3*i+2), tablero->obtenerDato(3*i), -40);
        }
        if (contVert == 2)
        {
            tablero->cambiarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+3), 10);
            tablero->cambiarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+6), 10);
            tablero->cambiarArista(tablero->obtenerDato(i+3), tablero->obtenerDato(i), 10);
            tablero->cambiarArista(tablero->obtenerDato(i+6), tablero->obtenerDato(i), 10);
        }
        if (contHor == 2)
        {
            tablero->cambiarArista(tablero->obtenerDato(3*i), tablero->obtenerDato(3*i+1), 10);
            tablero->cambiarArista(tablero->obtenerDato(3*i), tablero->obtenerDato(3*i+2), 10);
            tablero->cambiarArista(tablero->obtenerDato(3*i+1), tablero->obtenerDato(3*i), 10);
            tablero->cambiarArista(tablero->obtenerDato(3*i+2), tablero->obtenerDato(3*i), 10);
        }
    }
    if (contDiagDer == -2)
    {
        tablero->cambiarArista(tablero->obtenerDato(0), tablero->obtenerDato(4), -40);
        tablero->cambiarArista(tablero->obtenerDato(0), tablero->obtenerDato(8), -40);
        tablero->cambiarArista(tablero->obtenerDato(4), tablero->obtenerDato(0), -40);
        tablero->cambiarArista(tablero->obtenerDato(8), tablero->obtenerDato(0), -40);
    }
    if (contDiagIzq == -2)
    {
        tablero->cambiarArista(tablero->obtenerDato(2), tablero->obtenerDato(4), -40);
        tablero->cambiarArista(tablero->obtenerDato(2), tablero->obtenerDato(6), -40);
        tablero->cambiarArista(tablero->obtenerDato(6), tablero->obtenerDato(2), -40);
        tablero->cambiarArista(tablero->obtenerDato(4), tablero->obtenerDato(2), -40);
    }
    if (contDiagDer == 2)
    {
        tablero->cambiarArista(tablero->obtenerDato(0), tablero->obtenerDato(4), 10);
        tablero->cambiarArista(tablero->obtenerDato(0), tablero->obtenerDato(8), 10);
        tablero->cambiarArista(tablero->obtenerDato(4), tablero->obtenerDato(0), 10);
        tablero->cambiarArista(tablero->obtenerDato(8), tablero->obtenerDato(0), 10);
    }
    if (contDiagIzq == 2)
    {
        tablero->cambiarArista(tablero->obtenerDato(2), tablero->obtenerDato(4), 10);
        tablero->cambiarArista(tablero->obtenerDato(2), tablero->obtenerDato(6), 10);
        tablero->cambiarArista(tablero->obtenerDato(6), tablero->obtenerDato(2), 10);
        tablero->cambiarArista(tablero->obtenerDato(4), tablero->obtenerDato(2), 10);
    }
    return '_';
}

void turnoJugador(Grafo<Espacio>* tablero)
{
    int valor = 0;
    cout << "\nTu turno!! Escribe un numero de 1 a 9 para poner tu O" << endl;
    while (true){
        cin >> valor;
        if (tablero->obtenerDato(valor-1).caracter != '_'){
            cout << "Ese ya esta ocupado! escoje un espacio vacio" << endl;
            continue;
        }
        Espacio aux;
        aux.caracter = 'O';
        aux.numEspacio = valor-1;
        tablero->cambiarVertice(tablero->obtenerDato(valor-1), aux);
        alterarAristas(tablero, valor-1, -4);
        break;
    }
}

int main()
{
    Grafo<Espacio>* tablero = new Grafo<Espacio>();
    char ganador = '_';
    crearTablero(tablero);
    cout << "\nBienvenido al triqui! Juguemos. Yo sere las X y tu las O. Yo empiezo!" << endl;
    while (true)
    {
        turnoMaquinaMax(tablero);
        if (imprimirTablero(tablero) == 0)
            break;
        cout << endl;
        ganador = verificarGanador(tablero);
        if (ganador != '_')
            break;
        turnoJugador(tablero);
        if (imprimirTablero(tablero) == 0)
            break;
        cout << endl;
        ganador = verificarGanador(tablero);
        if (verificarGanador(tablero) != '_')
            break;
    }
    if (ganador == 'X')
        cout << "He ganado!" << endl;
    else if (ganador == 'O')
        cout << "Has ganado!" << endl;
    else
        cout << "Empatamos!" << endl;
    delete tablero;
    return 0;
}
