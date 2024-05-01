#include <iostream>
#include <fstream>
#include "iColores.h"
#include <time.h>
#include "memoryleaks.h"
#include "iJugador.h"

using namespace std;

void establecerPasos(int& pasos) {
	do {
		std::cout << "Indica el numero de pasos para crear el tablero aleatorio (mayor a 0): ";
		cin >> pasos;
	} while (pasos <= 0);
}

void menu(Juego& juego) {
	int pasos = 0;
	establecerPasos(pasos);			
	genera(juego, pasos);
}

bool comenzarSolitario(ListaJuegos& listaJuegos, Juego& juego) {
	bool seguirJugando = true;
	
	std::cout << "--- Comienza el SOLITARIO ---\n";
	while (!juegoFinalizado(juego) && seguirJugando) { // partida no finalizado
		mostrar(juego);
		seguirJugando = siguienteTurno(juego);
		if(seguirJugando) std::system("cls");
	}
	
	if (seguirJugando) { 
		mostrar(juego);
		std::cout << motivoFinPartida(juego) << endl;
		borrar(listaJuegos, &juego);
	}
	seguirJugando = quiereVolverAJugar(); // S = volver a cargar partidas / N = logout
 	system("cls");
	return seguirJugando;
}

void buscarPartida(ListaJugadores& listaJugadores, std::string nombre, bool& continuar) {
	Jugador* jugador = buscar(listaJugadores, nombre);
	continuar = true;

	while (continuar) {
		if (jugador == NULL) {
			jugador = new Jugador();
			inicializar(*jugador, nombre);
			insertar(listaJugadores, jugador);
			std::cout << "No tienes partidas. Vamos a crear un juego aleatorio\n";
			Juego* juego = new Juego();
			menu(*juego);
			insertar(jugador->partidas, juego);
			continuar = comenzarSolitario(jugador->partidas, *juego);
		}
		else {
			if (jugador->partidas.cont == 0) {
				std::cout << "No tienes partidas. Vamos a crear un juego aleatorio\n";
				Juego* juego = new Juego();
				menu(*juego);
				continuar = comenzarSolitario(jugador->partidas, *juego);
			}
			else {
				int numPartida = 0;
				std::cout << "--- Comienza el SOLITARIO ---\n";
				std::cout << "Tus partidas empezadas:\n";
				for (int i = 0; i < jugador->partidas.cont; i++) {
					std::cout << i+1 << " --------------------------\n";
					mostrar(*jugador->partidas.datos[i]);
					std::cout << "\n";
				}
				std::cout << "Elige una partida o 0 para crear una nueva aleatoria: ";
				std::cin >> numPartida;
				if (numPartida != 0) {
					system("cls");
					continuar = comenzarSolitario(jugador->partidas, *jugador->partidas.datos[numPartida - 1]);
				}
				else {
					system("cls");
					Juego *juego = new Juego();
					menu(*juego);
					insertar(jugador->partidas, juego);
					continuar = comenzarSolitario(jugador->partidas, *juego);
				}
			}
		}
	}
	if (!continuar) {
		if (jugador->partidas.cont == 0) {
			eliminar(listaJugadores, jugador);
		}
	}
}

void login(ListaJugadores& listaJugadores, bool& continuar) {
	std::string nombre;
	std::cout << "Usuario (FIN para terminar): ";
	std::cin >> nombre;

	if (nombre != "FIN")
		buscarPartida(listaJugadores, nombre, continuar);
	else continuar = true;
}

void cargarPartidas(ListaJugadores& listaJugadores) {
	ifstream fichero;
	fichero.open("partidas.txt");
	
	if (fichero.is_open()) {
		fichero >> listaJugadores.cont;
		listaJugadores.tam = listaJugadores.cont * 2;
		inicializar(listaJugadores, listaJugadores.tam);

		for (int i = 0; i < listaJugadores.cont; i++)
			fichero >> *(listaJugadores.datos[i]);

		fichero.close();
	}
	else {
		std::cout << "El archivo no se pudo abrir\n";
	}
}

void guardarPartidas(ListaJugadores& listaJugadores) {
	ofstream fichero;
	fichero.open("partidas.txt");
	if (fichero.is_open()) {
		fichero << listaJugadores.cont << "\n";
		for (int i = 0; i < listaJugadores.cont; i++) {
			fichero << (*listaJugadores.datos[i]);
		}
		fichero.close();
	}
	else {
		std::cout << "El archivo no se pudo abrir\n";
	}
	
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));
	ListaJugadores listaJugadores;
	cargarPartidas(listaJugadores);
	bool continuar = false;

	while (!continuar)
		login(listaJugadores, continuar);

	guardarPartidas(listaJugadores);
	system("pause");
	return 0;
}