#include "iMovimiento.h"
#include <fstream>

Posicion operator+ (const Posicion p, const Direccion d) {
	return { p.fila + d.difFila, p.columna + d.difColumna };
}

std::istream& operator>> (std::istream& in, Movimiento& movimiento) {
	in >> movimiento.origen.fila >> movimiento.origen.columna;	
	movimiento.origen.fila -= 1;
	movimiento.origen.columna -= 1;
	return in;
}