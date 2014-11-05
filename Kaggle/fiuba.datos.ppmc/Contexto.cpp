/*
 * Contexto.cpp
 *
 *  Created on: 19/10/2014
 *      Author: ezequiel
 */

#include "Contexto.h"

Contexto::Contexto(){
}

void Contexto::agregarPalabra(string unaPalabra){
	this->palabrasFrecuencias.insert(palabraFrecuencia(unaPalabra, 1));
}

Contexto::~Contexto() {
	// TODO Auto-generated destructor stub
}

