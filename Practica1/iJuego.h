#ifndef iJuego
#define iJuego

#include "iTablero.h"

const int MAX_PARTIDAS = 10;
struct Juego {
	Tablero tablero;
	bool ganado = false;
	bool bloqueado = false;
};

struct ListaJuegos {
	Juego* datos[MAX_PARTIDAS];
	int cont = 0;
};

void inicializar(ListaJuegos& l);
void insertar(ListaJuegos& l, Juego* j);
void borrar(ListaJuegos& l, Juego* j);
void liberar(ListaJuegos& l);

bool juegoFinalizado(const Juego j);
std::istream& operator>> (std::istream& in, Juego& j);
void mostrar(const Juego j);
bool siguienteTurno(Juego& j);
std::string motivoFinPartida(const Juego j);

bool pedirMovimiento(const Juego juego, Movimiento& mov);
void aplicarMovimiento(Juego& juego, const Movimiento mov);
void encontrarDireccionesPosibles(const Juego juego, Posicion origen,
	Direccion direccionesPosibles[4], int& n);
Direccion escogerDireccion(const Juego juego,
	const Direccion direccionesPosibles[4], const int numDirecciones);
void chequearGanador(Juego& juego, const Posicion pos);
void chequearBloqueo(Juego& juego);
bool quiereVolverAJugar();
void genera(Juego& juego, int pasos);

#endif