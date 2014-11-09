/*
 * Modelo0.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo0.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"
#include "../fiuba.datos.ppmc/Palabra.h"

Modelo0::Modelo0() {
	this->palabras = new vector<Palabra>;
}

//Se hashea la palabra para facilitar el ingreso de una palabra nueva
void Modelo0::agregarPalabra(Palabra unaPalabra){
	int primo = 5001;
	HashingUniversalS* unHash = new HashingUniversalS(primo);
	unsigned int indice = unHash->hashString(unaPalabra.getNombre());

	std::vector<Palabra>::iterator it;
	it = this->palabras->begin();
	std::advance(it,indice);
	this->palabras->insert(it, unaPalabra);
}

Modelo0::~Modelo0() {
	delete this->palabras;
}

