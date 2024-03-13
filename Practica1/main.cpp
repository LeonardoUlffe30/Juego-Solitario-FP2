#include <iostream>
#include <fstream>
#include "iJuego.h"
#include "iColores.h"
#include <time.h>

using namespace std;

int main() {
	srand(time(NULL));
	bool seguirJugando = true;
	while (seguirJugando) { // quiere seguir jugando
		cout << "--- Comienza el SOLITARIO --- " << endl;
		// leer tablero
		Juego juego;
		//ifstream fichero;
		//fichero.open("tablero.txt");
		//fichero >> juego;
		//fichero.close();
		genera(juego, 5);

		while (!juegoFinalizado(juego)) { // partida no finalizado
			mostrar(juego);
			siguienteTurno(juego);
			std::system("cls");
		}
		mostrar(juego);
		cout << motivoFinPartida(juego) << endl;
		seguirJugando = quiereVolverAJugar();
	}

	system("pause");
	return 0;
}