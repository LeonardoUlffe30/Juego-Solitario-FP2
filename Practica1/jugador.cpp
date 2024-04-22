#include "iJugador.h"

void inicializar(Jugador& j, std::string nombre) {
	j.nombre = nombre;
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
std::ostream& operator<<(std::ostream& out, Jugador& j) {
	out << j.nombre; //Lee el nombre
	out << j.partidas.cont; //Lee el numero de partidas
	for (int i = 0; i < j.partidas.cont; i++) { //Guarda los tableros
		Juego* juego;
		out << juego->tablero;
		j.partidas.datos[i] = juego;
		++i;
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
* Inserta en la lista el jugador que se pasa como par�metros.Recuerda 
* que se trata de una lista de punteros a Jugador.
* Si la lista estuviera llena, ampliar� el tama�o de la lista 
* usando memoria din�mica.La nueva lista debe ser suficientemente 
* grande para poder insertar dos jugadores adicionales antes de 
* necesitar ser ampliada.
*/
void insertar(ListaJugadores& lista, Jugador* j) {
	if (lista.cont < lista.tam) {
		lista.datos[lista.cont + 1] = j;
		lista.cont++;
	}
	else {
		ListaJugadores nuevaLista;
		inicializar(nuevaLista, lista.tam*2);
		for (int i = 0; i < lista.cont; ++i) {
			nuevaLista.datos[i] = lista.datos[i];
			nuevaLista.cont++;
		}
		liberar(lista);
		lista = nuevaLista;
	}
}

/*
Elimina al jugador de la lista.Si al realizar la eliminaci�n, la lista
quedar� con 5 o m�s posiciones vac�as, se realizar� una disminuci�n del
tama�o din�mica de la lista.La nueva lista deber� contar solo con dos 
posiciones vac�as adem�s de las necesarias para el contenido de la 
lista. Adem�s de eliminar al jugador de la lista, esta funci�n se 
encargar� de liberar cualquier memoria din�mica utilizada por este.
*/
void eliminar(ListaJugadores& lista, Jugador* j) {
	delete j;
	lista.cont--;
	if (lista.cont < 5) {
		int tamDisminuido = lista.cont + 2;
		ListaJugadores nuevaLista;
		inicializar(nuevaLista, tamDisminuido);
		for (int i = 0; i < lista.cont; ++i) {
			nuevaLista.datos[i] = lista.datos[i];
			nuevaLista.cont++;
		}
		liberar(lista);
		lista = nuevaLista;
	}
}

/* Se asegura que se libera cualquier memoria din�mica utilizada por 
 * el jugador.T�picamente se encarga de llamar a la funci�n liberar 
   del m�dulo ListaJuegos.
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