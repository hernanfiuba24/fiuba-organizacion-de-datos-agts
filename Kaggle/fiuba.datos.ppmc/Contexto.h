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
#include <iostream>
#include "../fiuba.datos.hashing/HashingUniversalS.h"

class Contexto {
private:
	string nombre;
	list<Palabra*>* palabras;
	HashingUniversalS* unHash;
	int hashearPalabra(Palabra* unaPalabra);

public:
	Contexto(std::string unNombre, int primo);
	void agregarPalabra(Palabra* unaPalabra);
	string getNombre();
	virtual ~Contexto();
};

#endif /* FIUBA_DATOS_PPMC_CONTEXTO_H_ */
