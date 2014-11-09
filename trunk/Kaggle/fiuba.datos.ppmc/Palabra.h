/*
 * Palabra.h
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#ifndef FIUBA_DATOS_PPMC_PALABRA_H_
#define FIUBA_DATOS_PPMC_PALABRA_H_
#include <string>

using namespace std;

class Palabra {
public:
	Palabra(string unNombre);
	string getNombre();
	void incrementarFrecuencia();

private:
	size_t frecuencia;
	string nombre;
};

#endif /* FIUBA_DATOS_PPMC_PALABRA_H_ */
