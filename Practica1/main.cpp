#include <iostream>
#include <fstream>
#include "iJuego.h"
#include "iColores.h"
#include <time.h>

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

int main() {
	srand(time(NULL));
	bool seguirJugando = true;
	while (seguirJugando) { // quiere seguir jugando
		// leer tablero
		Juego juego;
		menu(juego);
		cout << "\n--- Comienza el SOLITARIO ---\n";

		while (!juegoFinalizado(juego)) { // partida no finalizado
			mostrar(juego);
			siguienteTurno(juego);
			std::system("cls");
		}
		mostrar(juego);
		cout << motivoFinPartida(juego) << endl;
		seguirJugando = quiereVolverAJugar();
		system("cls");
	}

	system("pause");

	return 0;
}