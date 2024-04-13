#include <iostream>
#include <fstream>
#include "iColores.h"
#include <time.h>
#include "memoryleaks.h"
#include "iJugador.h"

using namespace std;

void establecerPasos(int& pasos) {
	do {
		std::cout << "Ingrese el numero de pasos para generar el tablero (mayor a 0): ";
		cin >> pasos;
	} while (pasos <= 0);
}

void establecerDimension(int& dimension) {
	char respuesta = 0;
	do {
		std::cout << "Deseas establecer alguna dimension? (S/N): ";
		std::cin >> respuesta;
		if (respuesta == 'S') {
			std::cout << "Ingresa la dimension (Max 10x10): ";
			std::cin >> dimension;
		}
	} while (respuesta != 'S' && respuesta != 'N');
}

void menu(Juego& juego) {
	char respuesta;
	do {
		std::cout << "Deseas generar el tablero aleatoriamente? (S/N): ";
		std::cin >> respuesta;
		if (respuesta == 'N') {
			ifstream fichero;
			fichero.open("tablero.txt");
			fichero >> juego;
			fichero.close();
		}
		if (respuesta == 'S') {
			int pasos = 0, dimension = 6;
			establecerDimension(dimension);
			establecerPasos(pasos);			
			genera(juego, pasos, dimension);
		}
	} while (respuesta != 'S' && respuesta != 'N');
}

bool comenzarSolitario(Juego& juego) {
	bool seguirJugando = true;
	while (seguirJugando) { // quiere seguir jugando
		// leer tablero
		Juego juego;
		menu(juego);
		cout << "\n--- Comienza el SOLITARIO ---\n";
		mostrar(juego);
		while (!juegoFinalizado(juego)) { // partida no finalizado
			if (!siguienteTurno(juego))
				return false;
			std::system("cls");
			mostrar(juego);
		}
		//mostrar(juego);
		cout << motivoFinPartida(juego) << endl;
		seguirJugando = quiereVolverAJugar();
		system("cls");
	}
	return true;
}

void buscarPartida(ListaJugadores listaJugadores, std::string nombre, bool& continuar) {
	Jugador* jugador = buscar(listaJugadores, nombre);

	if (jugador == NULL) {
		insertar(listaJugadores, jugador);
		std::cout << "No tienes partidas. Vamos a crear un juego aleatorio\n";
	}
	else {
		if (jugador->partidas.cont == 0) std::cout << "No tienes partidas. Vamos a crear un juego aleatorio\n";
		else {
			int numPartida = 0;
			for (int i = 0; i < jugador->partidas.cont; i++) {
				std::cout << i << " --------------------------\n";
				mostrar(*jugador->partidas.datos[i]);
				std::cout << "\n";
			}
			std::cout << "Elige una partida o 0 para crear una nueva aleatoria: ";
			std::cin >> numPartida;
			if (numPartida != 0) {
				continuar = comenzarSolitario(*jugador->partidas.datos[numPartida]);
			}
		}
	}
}

void login(ListaJugadores listaJugadores, bool& continuar) {
	std::string nombre;
	std::cout << "Usuario (FIN para terminar): ";
	std::cin >> nombre;
	if (nombre != "FIN") {
		buscarPartida(listaJugadores, nombre, continuar);
	}
}

void cargarPartidas(ListaJugadores& listaJugadores) {
	ifstream fichero;
	fichero.open("partidas.txt");
	
	fichero >> listaJugadores.cont;
	listaJugadores.tam = listaJugadores.cont * 2;
	inicializar(listaJugadores, listaJugadores.tam);

	for (int i = 0; i < listaJugadores.cont; i++) {
		fichero >> *(listaJugadores.datos[i]);
	}
	fichero.close();
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));
	ListaJugadores listaJugadores;
	cargarPartidas(listaJugadores);
	bool continuar = false;

	while (!continuar) {
		login(listaJugadores, continuar);
	}
	
	system("pause");
	return 0;
}