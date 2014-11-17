/*
 * Contexto.h
 *
 *  Created on: 19/10/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_PPMC_CONTEXTO_H_
#define FIUBA_DATOS_PPMC_CONTEXTO_H_

#include <string>
#include <list>
#include "Palabra.h"

class Contexto {
private:
	std::string nombre;
	std::list<Palabra*>* palabras;

public:
	Contexto(std::string unNombre);
	Contexto();
	void agregarPalabra(Palabra* unaPalabra);
	Palabra* devolverPalabra(Palabra* unaPalabra);
	Palabra* devolverPrimeraPalabra();
	bool esIgualA(Contexto* unContexto);
	std::string getNombre();
	virtual ~Contexto();
};

#endif /* FIUBA_DATOS_PPMC_CONTEXTO_H_ */
