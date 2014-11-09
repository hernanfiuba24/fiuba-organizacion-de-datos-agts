/*
 * Modelo0.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo0.h"

Modelo0::Modelo0() {
	this->palabras = new vector<Palabra>;
}

void Modelo0::agregarPalabra(Palabra unaPalabra){
	std::vector<Palabra>::iterator it;
	it = this->palabras->begin();
	it++;
	this->palabras->insert(it, unaPalabra);
}

Modelo0::~Modelo0() {
	delete this->palabras;
}

