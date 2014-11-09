/*
 * Modelo1.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo1.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"

Modelo1::Modelo1() {
	this->contextos = new vector<Contexto>;
}

//CORREGIR ESTO LA PROXIMA!!!!!!!!!!
void Modelo1::agregarContexto(Contexto unContexto){
	int primo = 7001;
	HashingUniversalS* unHash = new HashingUniversalS(primo);
	unsigned int indice = unHash->hashString(unContexto.getNombre());

	//std::vector<Palabra>::iterator it;
	//it = this->contextos->begin();
	//std::advance(it,indice);
	//this->palabras->insert(it, unaPalabra);
}

Modelo1::~Modelo1() {
	delete this->contextos;
}

