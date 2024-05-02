#include <iostream>
#include <fstream>
#include "iColores.h"
#include <time.h>
#include "memoryleaks.h"
#include "iJugador.h"

int establecerPasos() {
	int pasos = 0;

	do {
		std::cout << "Indica el numero de pasos para crear el tablero aleatorio (mayor a 0): ";
		std::cin >> pasos;
	} while (pasos <= 0);

	return pasos;
}

void menu(Juego& juego) {
	int pasos = establecerPasos();			
	genera(juego, pasos);
}

bool comenzarSolitario(ListaJuegos& listaJuegos, Juego& juego) {
	bool seguirJugando = true;
	
	std::cout << "--- Comienza el SOLITARIO ---\n";

	while (!juegoFinalizado(juego) && seguirJugando) { // si partida no finalizada y true si no ha presionado 0
		mostrar(juego);
		seguirJugando = siguienteTurno(juego);
		if(seguirJugando) std::system("cls");
	}
	
	if (seguirJugando) { // true si se ha terminado por bloqueo o ganar
		mostrar(juego);
		std::cout << motivoFinPartida(juego) << std::endl;
		borrar(listaJuegos, &juego); // borro la partida por bloqueo o ganar
	}

	seguirJugando = quiereVolverAJugar(); // S = volver a cargar partidas, N = logout

 	system("cls");
	return seguirJugando;
}

void jugadorInexistente(ListaJugadores& listaJugadores, Jugador*& jugador, std::string nombre, bool& continuar) {
	jugador = new Jugador(); // inicializa jugador
	inicializar(*jugador, nombre); // inicializa la lista de juegos del jugador
	insertar(listaJugadores, jugador); // inserta jugador en la lista de jugadores
	std::cout << "\nNo tienes partidas. Vamos a crear un juego aleatorio\n";
	Juego* juego = new Juego();
	menu(*juego); // crea tablero aleatorio
	insertar(jugador->partidas, juego); // inserta partida en la lista de juegos del jugador
	continuar = comenzarSolitario(jugador->partidas, *juego);
}

void jugadorExistenteSinPartidas(Jugador*& jugador, bool& continuar) {
	std::cout << "No tienes partidas. Vamos a crear un juego aleatorio\n";
	Juego* juego = new Juego(); // inicializa juego
	menu(*juego); // crea tablero aleatorio
	insertar(jugador->partidas, juego); // inserto partida en la lista de juegos del jugador
	continuar = comenzarSolitario(jugador->partidas, *juego);
}

void elegirPartida(Jugador* jugador, bool& continuar) {
	int numPartida = 0;
	std::cout << "Elige una partida o 0 para crear una nueva aleatoria: ";
	std::cin >> numPartida;

	if (numPartida != 0) { // elige una partida
		system("cls");
		continuar = comenzarSolitario(jugador->partidas, *jugador->partidas.datos[numPartida - 1]);
	}
	else { // crea una partida aleatoria 
		system("cls");
		Juego* juego = new Juego(); // inicializa juego
		menu(*juego); // crea tablero aleatorio
		insertar(jugador->partidas, juego); // inserta partida en la lista de juegos del jugador
		continuar = comenzarSolitario(jugador->partidas, *juego);
	}
}

void jugadorExistenteConPartidas(Jugador*& jugador, bool& continuar) {
	system("cls");
	std::cout << "--- Comienza el SOLITARIO ---\n";
	std::cout << "Tus partidas empezadas:\n";

	for (int i = 0; i < jugador->partidas.cont; i++) {
		std::cout << i + 1 << " --------------------------------\n";
		mostrar(*jugador->partidas.datos[i]);
		std::cout << "\n";
	}

	elegirPartida(jugador, continuar);
}

void comprobarEliminacionJugador(ListaJugadores& listaJugadores, Jugador* jugador) {
	if (jugador->partidas.cont == 0) eliminar(listaJugadores, jugador);
}

void buscarPartida(ListaJugadores& listaJugadores, std::string nombre, bool& continuar) {
	Jugador* jugador = buscar(listaJugadores, nombre);
	continuar = true;

	while (continuar) {
		if (jugador == NULL) jugadorInexistente(listaJugadores, jugador, nombre, continuar);
		else {
			if (jugador->partidas.cont == 0) jugadorExistenteSinPartidas(jugador, continuar);
			else jugadorExistenteConPartidas(jugador, continuar);
		}
	}

	comprobarEliminacionJugador(listaJugadores, jugador);
}

void login(ListaJugadores& listaJugadores, bool& continuar) {
	std::string nombre;
	std::cout << "Usuario (FIN para terminar): ";
	std::cin >> nombre;

	if (nombre != "FIN")
		buscarPartida(listaJugadores, nombre, continuar);
	else continuar = true;
}

void cargarFichero(ListaJugadores& listaJugadores) {
	std::ifstream fichero;
	fichero.open("partidas.txt");
	
	if (fichero.is_open()) {
		fichero >> listaJugadores.cont;
		listaJugadores.tam = listaJugadores.cont * 2;
		inicializar(listaJugadores, listaJugadores.tam);

		for (int i = 0; i < listaJugadores.cont; i++)
			fichero >> *(listaJugadores.datos[i]);

		fichero.close();

		ordenar(listaJugadores); // ordenar jugadores por nombre al cargar fichero
	}
	else std::cout << "El archivo no se pudo abrir\n";
}

void guardarFichero(ListaJugadores& listaJugadores) {
	std::ofstream fichero;
	fichero.open("partidas.txt");

	if (fichero.is_open()) {
		fichero << listaJugadores.cont << "\n";
		for (int i = 0; i < listaJugadores.cont; i++) {
			fichero << (*listaJugadores.datos[i]);
		}
		fichero.close();
	}
	else std::cout << "El archivo no se pudo abrir\n";
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));
	ListaJugadores listaJugadores;
	cargarFichero(listaJugadores);
	bool continuar = false;

	while (!continuar)
		login(listaJugadores, continuar);

	guardarFichero(listaJugadores);

	liberar(listaJugadores);
	system("pause");
	return 0;
}