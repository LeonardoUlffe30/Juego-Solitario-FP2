#include "iTablero.h"
#include "iCelda.h"

std::istream& operator>> (std::istream& in, Tablero& tablero) {
	int filaMeta, colMeta;
	in >> tablero.filas >> tablero.columnas;

	for (int i = 0; i < tablero.filas; ++i) {
		for (int j = 0; j < tablero.columnas; ++j) {
			in >> tablero.celdas[i][j];
		}
	}
	in >> filaMeta >> colMeta;
	tablero.celdas[filaMeta][colMeta].meta = true;
	return in;
}

void mostrar(const Tablero tablero) {
	std::cout << "   ";
	for (int i = 0; i < tablero.columnas; ++i) {
		std::cout << " " << i + 1 << "  ";
	}
	std::cout << "\n";
	for (int i = 0; i < tablero.filas; ++i) {
		std::cout << i+1 << " " << char(124);
		for (int j = 0; j < tablero.columnas; ++j) {
			mostrar(tablero.celdas[i][j]);
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

bool hayFicha(const Tablero tablero, const Posicion pos) {
	if (tablero.celdas[pos.fila][pos.columna].tipo == FICHA) return true;
	else return false;
}
bool hayVacia(const Tablero tablero, const Posicion pos) {
	if (tablero.celdas[pos.fila][pos.columna].tipo == VACIA) return true;
	else return false;
}

bool esNula(const Tablero tablero, const Posicion pos) {
	if (tablero.celdas[pos.fila][pos.columna].tipo == NULA) return true;
	else return false;
}

bool esMeta(const Tablero tablero, const Posicion pos) {
	if (tablero.celdas[pos.fila][pos.columna].meta) return true;
	else return false;
}

int contarFichas(const Tablero tablero) {
	int contador = 0;
	for (int i = 0; i < tablero.filas; ++i) {
		for (int j = 0; j < tablero.columnas; ++j) {
			if (tablero.celdas[i][j].tipo == FICHA)
				++contador;
		}
	}
	return contador;
}
void quitarFicha(Tablero& tablero, const Posicion pos) {
	tablero.celdas[pos.fila][pos.columna].tipo = VACIA;
}

void ponerFicha(Tablero& tablero, const Posicion pos) {
	tablero.celdas[pos.fila][pos.columna].tipo = FICHA;
}