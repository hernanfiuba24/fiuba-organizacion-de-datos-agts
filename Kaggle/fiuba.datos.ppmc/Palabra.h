/*
 * Palabra.h
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#ifndef FIUBA_DATOS_PPMC_PALABRA_H_
#define FIUBA_DATOS_PPMC_PALABRA_H_
#include <string>


class Palabra {
public:
	Palabra(std::string unNombre);
	std::string getNombre();
	void incrementarFrecuencia();
	bool esIgualA(Palabra* unaPalabra);

private:
	size_t frecuencia;
	std::string nombre;
};

#endif /* FIUBA_DATOS_PPMC_PALABRA_H_ */
