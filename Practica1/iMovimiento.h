#ifndef iMovimiento
#define iMovimiento

#include<string>

struct Posicion {
	int fila = -1;
	int columna = -1;
};
struct Direccion {
	int difFila = 0;
	int difColumna = 0;
	std::string nombre;
};

const int NUM_DIRECCIONES = 4;
const Direccion DIRECCIONES[] = { { -1, 0, "Arriba" },
								{ 1, 0, "Abajo" },
								{ 0, -1, "Izquierda" },
								{ 0, 1, "Derecha" } };
struct Movimiento {
	Posicion origen;
	Direccion dir;
};
// Calcula la posición resultante de mover en una dirección desde un origen
Posicion operator+ (const Posicion p, const Direccion d);
std::istream& operator>> (std::istream& in, Movimiento& movimiento);

#endif 
