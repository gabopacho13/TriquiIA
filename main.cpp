
//Gabriel Coronado
//Brayan Fajardo
//Mateo Henao
#include <iostream>
#include "grafo.h"
#include "espacio.h"

using namespace std;

//Esta funcion conecta cada espacio con los demás relevantes en el triqui (horizontales, verticales y Diagonales si aplican)
void crearTablero(Grafo<Espacio>* tablero)
{
    for (int i = 0; i < 9; i++)
    {
        Espacio espacio;
        espacio.numEspacio = i;
        espacio.caracter = '_';
        tablero->insertarVertice(espacio);
    }
    //Crear aristas. Cada arista comienza con un valor de 1. La suma de los valores de las aristas de un espacio es la suma heuristica
    for (int i = 0; i < 9; i++)
    {
        //Crear aristas horizontales para los espacios de la primera columna
        if ((i%3)== 0)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+1), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+2), 1);
        }
        //Crear aristas horizontales para los espacios de la segunda columna
        if ((i%3)== 1)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-1), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+1), 1);
        }
        //Crear aristas horizontales para los espacios de la tercera columna
        if ((i%3)== 2)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-1), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-2), 1);
        }
        //Crear aristas verticales para los espacios de la primera fila
        if (i < 3)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+3), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+6), 1);
        }
        //Crear aristas verticales para los espacios de la segunda fila
        if (i>=3 && i<6)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-3), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+3), 1);
        }
        //Crear aristas verticales para los espacios de la tercera fila
        if (i >= 6)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-3), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-6), 1);
        }
        //crear aristas diagonales para el espacio 0
        if (i == 0)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+4), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+8), 1);
        }
        //Crear aristas diagonales para el espacio 2
        if (i == 2)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+2), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+4), 1);
        }
        //Crear aristas diagonales para el espacio 4
        if (i == 4)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-4), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-2), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+2), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+4), 1);
        }
        //Crear aristas diagonales para el espacio 6
        if (i == 6)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-2), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-4), 1);
        }
        //Crear aristas diagonales para el espacio 8
        if (i == 8)
        {
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-4), 1);
            tablero->insertarArista(tablero->obtenerDato(i), tablero->obtenerDato(i-8), 1);
        }
    }
}

//Imprime el tablero al jugador
int imprimirTablero(Grafo<Espacio>* tablero)
{
    int cont = 0;
    //Contador de filas
    for (int i = 0; i < 3; i++)
    {
        //Contador de columnas
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

// cambia el valor de todas las aristas conectadas al espacio en el indice recibido
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

// revisa los espacios disponibles tras simular una X en el espacio indiceX
// Analiza las posibilidades del jugador usando la heuristica y restando al valor de sumaHeuristica el valor obtenido, dando como resultado el total del análisis
void turnoMaquinaMin(Grafo<Espacio>* tablero, int indiceX, int &sumaHeuristica)
{
    int minimo = 999;
    for (int i = 0; i < 9; i++)
    {
        //Ignorar el espacio donde supuestamente habria una X
        if (i == indiceX)
            continue;
        //Simular una O en el espacio i si este esta vacio
        if (tablero->obtenerDato(i).caracter == '_')
        {
            int posMinimo = 0;
            //restar al valor de las aristas conectadas al espacio i
            alterarAristas(tablero, i, -4);
            //Definir que tan problemática sería la jugada del jugador si pusiera O en el espacio i
            for (int j = 0; j < 9; j++)
            {
                if (tablero->obtenerDato(j).caracter == '_' || tablero->obtenerDato(j).caracter == 'O')
                {
                    posMinimo += tablero->buscarArista(tablero->obtenerDato(i), tablero->obtenerDato(j));
                }
            }
            //almacenar el valor minimo de las posibles jugadas del jugador
            if (posMinimo < minimo)
                minimo = posMinimo;
            //Devolver los valores de las aristas a su valor inicial
            alterarAristas(tablero, i, 4);
        }
    }
    //Restar el mínimo a la suma heurística
    sumaHeuristica += minimo;
}

//Comienza el turno de la maquina
//La maquina revisa cada espacio y los valores de las aristas conectadas (Que determinan el valor heurístico de la jugada) y suma el valor de la mejor jugada a la sumaHeuristica
//A la jugada se le resta lo calculado durante la minimización (turnoMaquinaMax)
void turnoMaquinaMax(Grafo<Espacio>* tablero)
{
    cout << "Es mi turno!!" << endl;
    int maximo = -999;
    int indiceMejor = 1;
    //Revisar todos los espacios disponibles
    for (int i = 0; i < 9; i++)
    {
        //Simular una jugada de la maquina en el espacio i
        if (tablero->obtenerDato(i).caracter == '_')
        {
            //cambiar los valores de las aristas conectadas a i
            alterarAristas(tablero, i, 1);
            int sumaHeuristica = 0;
            //Definir que tan beneficiosa sería esa jugada para la maquina comparando con los espacios vacios adyacentes.
            for (int j = 0; j < 9; j++)
            {
                if (tablero->obtenerDato(j).caracter == '_' || tablero->obtenerDato(j).caracter == 'X')
                    sumaHeuristica += tablero->buscarArista(tablero->obtenerDato(i), tablero->obtenerDato(j));
            }
            //Calcular que tanto se minimizó el riesgo con la supuesta jugada
            turnoMaquinaMin(tablero, i, sumaHeuristica);
            //Almacenar los datos de la jugada si esta ha sido la mejor hasta ahora
            if (sumaHeuristica > maximo)
            {
                maximo = sumaHeuristica;
                indiceMejor = i;
            }
            //Devolver las aristas a su valor inicial
            alterarAristas(tablero, i, -1);
        }
    }
    while (true)
    {
        //Realizar la jugada determinada
        if (tablero->obtenerDato(indiceMejor).caracter == '_')
        {
            Espacio aux;
            aux.numEspacio = indiceMejor;
            aux.caracter = 'X';
            //Actualizar el tablero
            tablero->cambiarVertice(tablero->obtenerDato(indiceMejor), aux);
            alterarAristas(tablero, indiceMejor, 1);
            break;
        }
        else
            //Buscar otra jugada en caso de que no se haya determinado un mejor caso y el espacio seleccionado esté ocupado
            indiceMejor++;
    }
}

//Revisa el estado actual del tablero
char verificarGanador(Grafo<Espacio>* tablero)
{
    int contDiagDer = 0;
    int contDiagIzq = 0;
    //Revisar el contenido de todos los espacios
    //Contador de filas
    for (int i = 0; i < 3; i++)
    {
        int contHor = 0;
        int contVert = 0;
        //Contador de columnas
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
        //Caso: Maquina gana
        if (contVert == 3 || contHor == 3 || contDiagDer == 3 || contDiagIzq == 3)
            return 'X';
        //Caso: Jugador gana
        if (contVert == -3 || contHor == -3 || contDiagDer == -3 || contDiagIzq == -3)
            return 'O';
        //Caso: Jugador a punto de lograr un triqui vertical. Cambiar valor de dos aristas en esa columna para anunciar estado de alerta
        if (contVert == -2)
        {
            tablero->cambiarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+3), -40);
            tablero->cambiarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+6), -40);
            tablero->cambiarArista(tablero->obtenerDato(i+3), tablero->obtenerDato(i), -40);
            tablero->cambiarArista(tablero->obtenerDato(i+6), tablero->obtenerDato(i), -40);
        }
        //Caso: Jugador a punto de lograr un triqui horizontal. Cambiar valor de dos aristas en esa columna para anunciar estado de alerta
        if (contHor == -2)
        {
            tablero->cambiarArista(tablero->obtenerDato(3*i), tablero->obtenerDato(3*i+1), -40);
            tablero->cambiarArista(tablero->obtenerDato(3*i), tablero->obtenerDato(3*i+2), -40);
            tablero->cambiarArista(tablero->obtenerDato(3*i+1), tablero->obtenerDato(3*i), -40);
            tablero->cambiarArista(tablero->obtenerDato(3*i+2), tablero->obtenerDato(3*i), -40);
        }
        //Caso: Maquina a punto de lograr un triqui vertical. Cambiar valor de dos aristas en esa columna para anunciar estado de ventaja
        if (contVert == 2)
        {
            tablero->cambiarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+3), 10);
            tablero->cambiarArista(tablero->obtenerDato(i), tablero->obtenerDato(i+6), 10);
            tablero->cambiarArista(tablero->obtenerDato(i+3), tablero->obtenerDato(i), 10);
            tablero->cambiarArista(tablero->obtenerDato(i+6), tablero->obtenerDato(i), 10);
        }
        //Caso: Maquina a punto de lograr un triqui vertical. Cambiar valor de dos aristas en esa columna para anunciar estado de ventaja
        if (contHor == 2)
        {
            tablero->cambiarArista(tablero->obtenerDato(3*i), tablero->obtenerDato(3*i+1), 10);
            tablero->cambiarArista(tablero->obtenerDato(3*i), tablero->obtenerDato(3*i+2), 10);
            tablero->cambiarArista(tablero->obtenerDato(3*i+1), tablero->obtenerDato(3*i), 10);
            tablero->cambiarArista(tablero->obtenerDato(3*i+2), tablero->obtenerDato(3*i), 10);
        }
    }
    //Caso: Jugador a punto de lograr un triqui en la diagonal 0-4-8. Cambiar valor de dos aristas en esa diagonal para anunciar estado de alerta
    if (contDiagDer == -2)
    {
        tablero->cambiarArista(tablero->obtenerDato(0), tablero->obtenerDato(4), -40);
        tablero->cambiarArista(tablero->obtenerDato(0), tablero->obtenerDato(8), -40);
        tablero->cambiarArista(tablero->obtenerDato(4), tablero->obtenerDato(0), -40);
        tablero->cambiarArista(tablero->obtenerDato(8), tablero->obtenerDato(0), -40);
    }
    //Caso: Jugador a punto de lograr un triqui en la diagonal 2-4-6. Cambiar valor de dos aristas en esa diagonal para anunciar estado de alerta
    if (contDiagIzq == -2)
    {
        tablero->cambiarArista(tablero->obtenerDato(2), tablero->obtenerDato(4), -40);
        tablero->cambiarArista(tablero->obtenerDato(2), tablero->obtenerDato(6), -40);
        tablero->cambiarArista(tablero->obtenerDato(6), tablero->obtenerDato(2), -40);
        tablero->cambiarArista(tablero->obtenerDato(4), tablero->obtenerDato(2), -40);
    }
    //Caso: Maquina a punto de lograr un triqui en la diagonal 0-4-8. Cambiar valor de dos aristas en esa diagonal para anunciar estado de ventaja
    if (contDiagDer == 2)
    {
        tablero->cambiarArista(tablero->obtenerDato(0), tablero->obtenerDato(4), 10);
        tablero->cambiarArista(tablero->obtenerDato(0), tablero->obtenerDato(8), 10);
        tablero->cambiarArista(tablero->obtenerDato(4), tablero->obtenerDato(0), 10);
        tablero->cambiarArista(tablero->obtenerDato(8), tablero->obtenerDato(0), 10);
    }
    //Caso: Maquina a punto de lograr un triqui en la diagonal 2-4-6. Cambiar valor de dos aristas en esa diagonal para anunciar estado de ventaja
    if (contDiagIzq == 2)
    {
        tablero->cambiarArista(tablero->obtenerDato(2), tablero->obtenerDato(4), 10);
        tablero->cambiarArista(tablero->obtenerDato(2), tablero->obtenerDato(6), 10);
        tablero->cambiarArista(tablero->obtenerDato(6), tablero->obtenerDato(2), 10);
        tablero->cambiarArista(tablero->obtenerDato(4), tablero->obtenerDato(2), 10);
    }
    return '_';
}

//Permite al jugador realizar su jugada
void turnoJugador(Grafo<Espacio>* tablero)
{
    int valor = 0;
    cout << "\nTu turno!! Escribe un numero de 1 a 9 para poner tu O" << endl;
    while (true){
        cin >> valor;
        //Verificar que el espacio exista
        if (valor < 1 || valor > 9){
            cout << "Ese espacio no existe! Escoje un espacio del 1 al 9" << endl;
            continue;
        }
        //Verificar que el espacio no esté ocupado
        if (tablero->obtenerDato(valor-1).caracter != '_'){
            cout << "Ese ya esta ocupado! escoje un espacio vacio" << endl;
            continue;
        }
        //Actualizar datos del tablero
        Espacio aux;
        aux.caracter = 'O';
        aux.numEspacio = valor-1;
        tablero->cambiarVertice(tablero->obtenerDato(valor-1), aux);
        //Asignar nuevo valor a las aristas que rodean el espacio seleccionado
        alterarAristas(tablero, valor-1, -4);
        break;
    }
}

int main()
{
    Grafo<Espacio>* tablero = new Grafo<Espacio>();
    char ganador = '_';
    crearTablero(tablero);
    cout << "\nBienvenido al triqui! Modo de uso:" << endl;
    //Imprimir modo de uso
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << 3*i+j+1 << " ";
        }
        cout << endl;
    }
    cout << "Juguemos. Yo sere las X y tu las O. Yo empiezo!" << endl;
    //Comenzar juego
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
    cout << "Si quieres volver a jugar, te estare esperando!" << endl;
    delete tablero;
    return 0;
}
