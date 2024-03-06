#include "iCelda.h"
#include "iColores.h"

std::istream& operator>>(std::istream& in, Celda& c) {
	int tipo;
	in >> tipo;
	if (tipo == 0) c.tipo = NULA;
	else {
		if (tipo == 1) c.tipo = VACIA;
		else c.tipo = FICHA;
	}
	return in;
}

void mostrar(const Celda c) {
	switch (c.tipo) {
	case NULA:
		std::cout << " " << " " << " " << char(124);
		break;
	case VACIA:
		if (c.meta)
			std::cout << BG_ORANGE << YELLOW << " * " << RESET << char(124);
		else
			std::cout << BG_ORANGE << "   " << RESET << char(124);
		break;
	case FICHA:
		if (c.meta)
			std::cout << BG_BLUE << YELLOW << " * " << RESET << char(124);
		else
			std::cout << BG_BLUE << "   " << RESET << char(124);
		break;
	default:
		break;
	}
}