#include <iostream>
#include <fstream>
#include "iJuego.h"
#include "iColores.h"

using namespace std;

int main() {
	bool seguirJugando = true;
	while (seguirJugando) { // quiere seguir jugando
		cout << "--- Comienza el SOLITARIO --- " << endl;
		// leer tablero
		Juego juego;
		ifstream fichero;
		fichero.open("tablero.txt");
		fichero >> juego;
		fichero.close();
		while (!juegoFinalizado(juego)) { // partida no finalizado
			mostrar(juego);
			siguienteTurno(juego);
		}
		mostrar(juego);
		cout << motivoFinPartida(juego) << endl;
		seguirJugando = quiereVolverAJugar();
	}

	system("pause");
	return 0;
}