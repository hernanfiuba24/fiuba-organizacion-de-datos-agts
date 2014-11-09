/*
 * Modelo1.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo1.h"

Modelo1::Modelo1() {
	this->contextos = new vector<Contexto>;
}

void Modelo1::agregarContexto(Contexto unContexto){
	std::vector<Contexto>::iterator it;
	it = this->contextos->begin();
	it++;
	this->contextos->insert(it, unContexto);
}

Modelo1::~Modelo1() {
	delete this->contextos;
}

