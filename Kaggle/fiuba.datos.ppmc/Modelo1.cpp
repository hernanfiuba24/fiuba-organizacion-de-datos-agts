/*
 * Modelo1.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo1.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"

Modelo1::Modelo1(int primo) {
	this->contextos = new vector<Contexto*>;
	this->unHash = new HashingUniversalS(primo);

}

//CORREGIDO!!!
void Modelo1::agregarContexto(Contexto* unContexto){
	unsigned int indice = this->unHash->hashString(unContexto->getNombre());

	Palabra* unEscape = new Palabra("esc");
	unContexto->agregarPalabra(unEscape);

	std::vector<Contexto*>::iterator it;
	it = this->contextos->begin();
	std::advance(it,indice);
	this->contextos->insert(it, unContexto);

}

Modelo1::~Modelo1() {
	delete this->contextos;
}

