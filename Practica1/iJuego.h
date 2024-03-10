#ifndef iJuego
#define iJuego

#include "iTablero.h"

struct Juego {
	Tablero tablero;
	bool ganado = false;
	bool bloqueado = false;
};
bool juegoFinalizado(const Juego j);
std::istream& operator>> (std::istream& in, Juego& j);
void mostrar(const Juego j);
void siguienteTurno(Juego& j);
std::string motivoFinPartida(const Juego j);

Movimiento pedirMovimiento(const Juego juego);
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