#ifndef iTablero
#define iTtablero

#include "iCelda.h"
#include "iMovimiento.h"

const int MAXDIM = 10;
struct Tablero {
	Celda celdas[MAXDIM][MAXDIM];
	int filas, columnas;
};

std::istream& operator>> (std::istream& in, Tablero& tablero);
void mostrar(const Tablero tablero);
bool hayFicha(const Tablero tablero, const Posicion pos);
bool hayVacia(const Tablero tablero, const Posicion pos);
bool esMeta(const Tablero tablero, const Posicion pos);
int contarFichas(const Tablero tablero);
void quitarFicha(Tablero& tablero, const Posicion pos);
void ponerFicha(Tablero& tablero, const Posicion pos);

#endif