#include "iJugador.h"
#include "memoryleaks.h"

void inicializar(Jugador& j, std::string nombre) {
	j.nombre = nombre;
	inicializar(j.partidas);
}

void inicializar(ListaJugadores& lista, int tam) { // lista es un puntero a un puntero de Juego
	lista.datos = new Jugador*[tam];
	lista.tam = tam;;
	for (int i = 0; i < tam; ++i) {
		lista.datos[i] = new Jugador();
	}
}

std::istream& operator>>(std::istream& in, Jugador& j) { 
	in >> j.nombre; //Lee el nombre
	in >> j.partidas.cont; //Lee el numero de partidas
	inicializar(j.partidas);
	for (int i = 0; i < j.partidas.cont; i++) { //Guarda los tableros
		in >> (j.partidas.datos[i]->tablero);
	}
	return in;
}

//Jugador 
//   string nombres;
//	 ListaJuegos partidas;
std::ostream& operator<<(std::ostream& out, Jugador& jugador) {
	out << jugador.nombre << "\n"; //Lee el nombre
	out << jugador.partidas.cont << "\n"; //Lee el numero de partidas
	for (int i = 0; i < jugador.partidas.cont; i++) { //Guarda los tableros
		out << jugador.partidas.datos[i]->tablero;;
	}
	return out;
}

Jugador* buscar(ListaJugadores lista, std::string nombre) {
	for (int i = 0; i < lista.cont; i++) {
		if (lista.datos[i]->nombre == nombre)
			return lista.datos[i];
	}
	return NULL;
}

/*
* Inserta en la lista el jugador que se pasa como parámetros.Recuerda 
* que se trata de una lista de punteros a Jugador.
* Si la lista estuviera llena, ampliará el tamaño de la lista 
* usando memoria dinámica.La nueva lista debe ser suficientemente 
* grande para poder insertar dos jugadores adicionales antes de 
* necesitar ser ampliada.
*/
void insertar(ListaJugadores& lista, Jugador* j) {
	if (lista.cont < lista.tam) { //4 elementos [0-3], cont 4, tam 4
		lista.datos[lista.cont] = j;
		lista.cont++;
	}
	else {
		ListaJugadores nuevaLista;
		inicializar(nuevaLista, lista.tam * 2);
		nuevaLista.cont = lista.cont;
		for (int i = 0; i < lista.cont; ++i) { // pasos los jugadores a la nueva lista
			inicializar(nuevaLista.datos[i]->partidas);
			nuevaLista.datos[i]->nombre = lista.datos[i]->nombre;
			nuevaLista.datos[i]->partidas.cont = lista.datos[i]->partidas.cont;
			for (int j = 0; j < lista.datos[i]->partidas.cont; j++) {
				nuevaLista.datos[i]->partidas.datos[j]->tablero = lista.datos[i]->partidas.datos[j]->tablero;
				nuevaLista.datos[i]->partidas.datos[j]->ganado = lista.datos[i]->partidas.datos[j]->ganado;
				nuevaLista.datos[i]->partidas.datos[j]->bloqueado = lista.datos[i]->partidas.datos[j]->bloqueado;
			}
		}
		 //3 elementos [0,2], cont = 3

		liberar(lista);
		lista = nuevaLista;
	}
}

/*
Elimina al jugador de la lista.Si al realizar la eliminación, la lista
quedará con 5 o más posiciones vacías, se realizará una disminución del
tamaño dinámica de la lista.La nueva lista deberá contar solo con dos 
posiciones vacías además de las necesarias para el contenido de la 
lista. Además de eliminar al jugador de la lista, esta función se 
encargará de liberar cualquier memoria dinámica utilizada por este.
*/
void eliminar(ListaJugadores& lista, Jugador* j) {
	liberar(j->partidas); //liberar los punteros a las partidas (de tipo Juego)
	delete j; // elimino el puntero al jugador
	lista.cont--;
	if (lista.cont < 5) {
		int tamDisminuido = lista.cont + 2;
		ListaJugadores nuevaLista;
		inicializar(nuevaLista, tamDisminuido);
		for (int i = 0; i < lista.cont; ++i) { // pasos los jugadores a la nueva lista
			inicializar(nuevaLista.datos[i]->partidas);
			nuevaLista.datos[i]->nombre = lista.datos[i]->nombre;
			nuevaLista.datos[i]->partidas.cont = lista.datos[i]->partidas.cont;
			for (int j = 0; j < lista.datos[i]->partidas.cont; j++) {
				nuevaLista.datos[i]->partidas.datos[j]->tablero = lista.datos[i]->partidas.datos[j]->tablero;
				nuevaLista.datos[i]->partidas.datos[j]->ganado = lista.datos[i]->partidas.datos[j]->ganado;
				nuevaLista.datos[i]->partidas.datos[j]->bloqueado = lista.datos[i]->partidas.datos[j]->bloqueado;
			}
			nuevaLista.cont = lista.cont;
		}

		liberar(lista);
		lista = nuevaLista;		
	}
}

/* Se asegura que se libera cualquier memoria dinámica utilizada por 
 * el jugador.Típicamente se encarga de llamar a la función liberar 
   del módulo ListaJuegos.
*/
void liberar(ListaJugadores& lista) {
	// Liberar memoria de cada jugador
	for (int i = 0; i < lista.cont; ++i) {
		liberar((*lista.datos)->partidas); // Liberar memoria de cada jugador individual
		delete lista.datos[i]; // Liberar memoria del puntero a jugador
	}
	// Liberar memoria del arreglo de punteros
	delete[] lista.datos;

	lista.cont = 0;
	lista.tam = 0;
}