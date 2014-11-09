/*
 /*
 * Contexto.cpp
 *
 *  Created on: 19/10/2014
 *      Author: ezequiel
 */

#include "Contexto.h"

Contexto::Contexto(){
	this->palabras = new list<Palabra>;
}

void Contexto::agregarPalabra(string unaPalabra){
	std::list<Palabra>::iterator it;
    it = this->palabras->begin();
    it++;
	this->palabras->insert(it, unaPalabra);
}

Contexto::~Contexto() {
	// TODO Auto-generated destructor stub
}
