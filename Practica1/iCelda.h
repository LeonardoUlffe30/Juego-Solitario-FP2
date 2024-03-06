#ifndef iCelda
#define iCelda

#include<iostream>

enum tipoCelda { NULA, VACIA, FICHA};

struct Celda {
	tipoCelda tipo;
	bool meta = false;
};

std::istream& operator>>(std::istream& in, Celda& c);
void mostrar(const Celda c);

#endif