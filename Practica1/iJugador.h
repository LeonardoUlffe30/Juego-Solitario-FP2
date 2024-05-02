#ifndef iJugador
#define iJugador

#include <iostream>
#include "iJuego.h"

struct Jugador {
	std::string nombre;
	ListaJuegos partidas;
};
struct ListaJugadores {
	Jugador **datos = NULL;
	int cont = 0;
	int tam = 0;
};

void inicializar(Jugador& j, std::string nombre);
void inicializar(ListaJugadores& lista, int tam);
std::istream& operator>>(std::istream& in, Jugador& j);
std::ostream& operator<<(std::ostream& out, Jugador& j);
Jugador* buscar(ListaJugadores lista, std::string nombre);
void insertar(ListaJugadores& lista, Jugador* j);
void eliminar(ListaJugadores& lista, Jugador* j);
void liberar(ListaJugadores& lista);
void ordenar(ListaJugadores& lista);

#endif
