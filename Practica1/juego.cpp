#include "iJuego.h"
#include "iColores.h"
#include <random>
#include "memoryleaks.h"

void inicializar(ListaJuegos& l) {
	for (int i = 0; i < MAX_PARTIDAS; ++i) 
		l.datos[i] = new Juego();
}

void insertar(ListaJuegos& l, Juego* j) {
	l.datos[l.cont] = j;
	l.cont++;
}

void borrar(ListaJuegos& l, Juego* j) {
	//Borrando partida
	int indice = 0;
	for (int i = 0; i < l.cont; i++) {
		if (l.datos[i] == j) {
			indice = i;
			delete l.datos[i];
		}
	}

	//Reordenando partidas
	if (indice == l.cont - 1) l.cont--;
	else {
		for (int i = indice; i < l.cont; i++) {
			l.datos[i] = l.datos[i+1];
			l.datos[i+1] = NULL;
		}
		l.cont--;
	}
}

void liberar(ListaJuegos& l) {
	for (int i = 0; i < l.cont; i++) 
		delete l.datos[i];
}

bool juegoFinalizado(const Juego juego) {
	if (juego.bloqueado || juego.ganado) {
		return true;
	}
	return false;
}

std::istream& operator>> (std::istream& in, Juego& j) {
	in >> j.tablero;
	return in;
}

void mostrar(const Juego j) {
	mostrar(j.tablero);
}

bool siguienteTurno(Juego& juego) {
	int n = 0;
	Movimiento movimiento; 
	Direccion direccionesPosibles[4];
	bool continuar = false;
	do {
		continuar = pedirMovimiento(juego, movimiento);
		if (!continuar) return continuar;
		encontrarDireccionesPosibles(juego, movimiento.origen, direccionesPosibles, n);
	} while (n == 0);
	if (n > 1) {
		movimiento.dir = escogerDireccion(juego, direccionesPosibles, n);
		aplicarMovimiento(juego, movimiento);
	}
	else {
		movimiento.dir = direccionesPosibles[0];
		aplicarMovimiento(juego, movimiento);
	}
	chequearBloqueo(juego);
	return continuar;
}

std::string motivoFinPartida(const Juego juego) {
	if (juego.ganado) {
		return "��� HAS GANADO !!!.";
	}
	else return "Has perdido. Es imposible realizar algun movimiento";
}

//Funciones auxiliares para implementar las anteriores
bool pedirMovimiento(const Juego juego, Movimiento& movimiento) {
	do {
		std::cout << "Escoja ficha (0 para salir): ";
		std::cin >> movimiento.origen.fila;
		if (movimiento.origen.fila == 0) {
			return false;
		}
		else std::cin >> movimiento.origen.columna;
		movimiento.origen.fila--;
		movimiento.origen.columna--;
	} while (juego.tablero.celdas[movimiento.origen.fila][movimiento.origen.columna].tipo == NULA ||
		movimiento.origen.fila >= juego.tablero.filas || movimiento.origen.fila < 0 ||
		movimiento.origen.columna >= juego.tablero.columnas || movimiento.origen.columna < 0);
	std::cout << "\n";
	return true;
}

void aplicarMovimiento(Juego& juego, const Movimiento mov) {
	Posicion posOrigen = mov.origen;
	Posicion posQuitar = mov.origen + mov.dir;
	Posicion posOcupar = mov.origen + mov.dir + mov.dir;
	quitarFicha(juego.tablero, posOrigen);
	quitarFicha(juego.tablero, posQuitar);
	ponerFicha(juego.tablero, posOcupar);
	chequearGanador(juego, posOcupar);
}

void encontrarDireccionesPosibles(const Juego juego, Posicion origen, Direccion direccionesPosibles[4], int& n) {
	int i = 0;

	while (i < 4) {
		bool arriba = origen.fila <= 1 && DIRECCIONES[i].nombre == "Arriba"; //verifico si salgo del limite si voy por arriba
		bool abajo = origen.fila >= juego.tablero.filas-2 && DIRECCIONES[i].nombre == "Abajo"; //verifico si salgo del limite si voy por abajo
		bool izquierda = origen.columna <= 1 && DIRECCIONES[i].nombre == "Izquierda"; //verifico si salgo del limite si voy por la izquierda
		bool derecha = origen.columna >= juego.tablero.columnas-2 && DIRECCIONES[i].nombre == "Derecha"; //verifico si salgo del limite si voy por la derecha
		if (!derecha && !izquierda && !arriba && !abajo) { //si todos son falsos significa que no salgo del limite
			Posicion celdaFicha = origen + DIRECCIONES[i];
			if (hayFicha(juego.tablero, celdaFicha)) {
				Posicion celdaVacia = celdaFicha + DIRECCIONES[i];
				if (hayVacia(juego.tablero, celdaVacia)) {
					direccionesPosibles[n] = DIRECCIONES[i];
					++n;
				}
			}
		}
		++i;
	}
}

Direccion escogerDireccion(const Juego juego, const Direccion direccionesPosibles[4], const int numDirecciones) {
	for (int i = 0; i < numDirecciones; ++i) {
		std::cout << i + 1 << ".- " << direccionesPosibles[i].nombre << "\n";
	}
	std::cout << "Escoja una direccion (";
	for (int i = 0; i < numDirecciones; ++i) {
		if (i == numDirecciones - 1)
			std::cout << i + 1 << "): ";
		else
			std::cout << i + 1 << ", ";
	}
	int seleccion;
	std::cin >> seleccion;
	return direccionesPosibles[seleccion-1];
}

void chequearGanador(Juego& juego, const Posicion pos) {
	if (contarFichas(juego.tablero) == 1 && esMeta(juego.tablero, pos) && hayFicha(juego.tablero, pos)) {
		juego.ganado = true;
	}
}

void chequearBloqueo(Juego& juego) {
	Direccion direccionesDisponibles[4];
	int fichasMover = 0;
	int i = 0, j = 0;
	while (i < juego.tablero.filas && fichasMover < 1) {
		j = 0;
		while (j < juego.tablero.columnas && fichasMover < 1) {
			if (hayFicha(juego.tablero, { i,j }))
				encontrarDireccionesPosibles(juego, { i,j }, direccionesDisponibles, fichasMover);
			++j;
		}
		++i;
	}
	if (fichasMover == 0) {
		juego.bloqueado = true;
	}
}

bool quiereVolverAJugar() {
	char opcion;
	do {
		std::cout << "\nNueva partida (S/N): ";
		std::cin >> opcion;
		if (opcion == 'S') {
			return true; 
		}
		else {
			if (opcion == 'N')
				return false;
		}
	} while (opcion != 'S' && opcion != 'N');
}

void encontrarDireccionesPosiblesAleatorio(const Juego juego, Posicion origen, Direccion direccionesPosibles[4], int& n) {
	int i = 0;

	while (i < 4) {
		bool arriba = origen.fila <= 1 && DIRECCIONES[i].nombre == "Arriba"; //verifico si salgo del limite si voy por arriba
		bool abajo = origen.fila >= juego.tablero.filas - 2 && DIRECCIONES[i].nombre == "Abajo"; //verifico si salgo del limite si voy por abajo
		bool izquierda = origen.columna <= 1 && DIRECCIONES[i].nombre == "Izquierda"; //verifico si salgo del limite si voy por la izquierda
		bool derecha = origen.columna >= juego.tablero.columnas - 2 && DIRECCIONES[i].nombre == "Derecha"; //verifico si salgo del limite si voy por la derecha
		if (!derecha && !izquierda && !arriba && !abajo) { //si todos son falsos significa que no salgo del limite
			Posicion celdaAnterior1 = origen + DIRECCIONES[i];
			if (hayVacia(juego.tablero, celdaAnterior1) || esNula(juego.tablero, celdaAnterior1)) {
				Posicion celdaAnterior2 = celdaAnterior1 + DIRECCIONES[i];
				if (hayVacia(juego.tablero, celdaAnterior2) || esNula(juego.tablero, celdaAnterior2)) {
					direccionesPosibles[n] = DIRECCIONES[i];
					++n;
				}
			}
		}
		++i;
	}
}

void aplicarMovimientoAleatorio(Juego& juego, const Movimiento mov) {
	Posicion posOrigen = mov.origen;
	Posicion posOcupar1 = mov.origen + mov.dir;
	Posicion posOcupar2 = mov.origen + mov.dir + mov.dir;
	quitarFicha(juego.tablero, posOrigen);
	ponerFicha(juego.tablero, posOcupar1);
	ponerFicha(juego.tablero, posOcupar2);
}

void genera(Juego& juego, int pasos) {
	int n = -1, nFichas = -1, dimension = 4 + rand() % (10 - 4 + 1); // [1;10]
	juego.tablero = { {NULA, false}, dimension, dimension };
	for (int i = 0; i < pasos && n != 0 && nFichas != 0; ++i) {
		Direccion direccionesPosibles[4];
		Movimiento mov;
		n = 0;  
		if (i == 0) {
			mov.origen = { rand() % (juego.tablero.filas), rand() % (juego.tablero.columnas) };
			juego.tablero.celdas[mov.origen.fila][mov.origen.columna].meta = true;
			ponerFicha(juego.tablero, mov.origen);
			std::cout << "Paso " << i + 1 << "\n";
			mostrar(juego);
			encontrarDireccionesPosiblesAleatorio(juego, mov.origen, direccionesPosibles, n);
			if (n != 0) {
				mov.dir = direccionesPosibles[rand() % n];
				aplicarMovimientoAleatorio(juego, mov);
			}
			mostrar(juego);
		}
		else {
			nFichas = 0;
			Posicion* posFichas = new Posicion[juego.tablero.filas * juego.tablero.columnas];

			encontrarFichas(juego.tablero, posFichas, nFichas);
			mov.origen = posFichas[rand() % nFichas];
			
			std::cout << "Paso " << i + 1 << "\n";
			if (nFichas != 0) {
				encontrarDireccionesPosiblesAleatorio(juego, mov.origen, direccionesPosibles, n);
				if (n != 0) {
					mov.dir = direccionesPosibles[rand() % n];
					aplicarMovimientoAleatorio(juego, mov);
				}
			}
			mostrar(juego);
		}
	}
}
