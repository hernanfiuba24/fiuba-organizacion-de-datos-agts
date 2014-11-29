/*
 * Palabra.h
 *
 *  Created on: 28/11/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_PPMC_PALABRA_H_
#define FIUBA_DATOS_PPMC_PALABRA_H_

#include <string>

class Palabra {
public:
	Palabra(std::string unaPalabra);
	std::string getPalabra();
	unsigned long getFrecuencia();
	void incrementarFrecuencia();
	void inicializarPalabra(std::string unaPalabra);


private:
	std::string palabra;
	unsigned long frecuencia;
};

#endif /* FIUBA_DATOS_PPMC_PALABRA_H_ */
