/*
 * Modelo1.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo1.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"

Modelo1::Modelo1() {
	this->contextos = new vector<Contexto*>;
}

//CORREGIDO!!!
void Modelo1::agregarContexto(Contexto* unContexto){
	int primo = 7001;
	HashingUniversalS* unHash = new HashingUniversalS(primo);
	unsigned int indice = unHash->hashString(unContexto->getNombre());

	std::vector<Contexto*>::iterator it;
	it = this->contextos->begin();
	std::advance(it,indice);
	this->contextos->insert(it, unContexto);
}

Modelo1::~Modelo1() {
	delete this->contextos;
}

