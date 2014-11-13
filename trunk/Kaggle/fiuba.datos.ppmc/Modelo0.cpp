/*
 * Modelo0.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo0.h"

using namespace std;

Modelo0::Modelo0(int primo) {
	this->palabras = new vector<Palabra*>;

	this->unHash = new HashingUniversalS(primo);
}

//Se hashea la palabra para facilitar el ingreso de una palabra nueva
void Modelo0::agregarPalabra(Palabra* unaPalabra){

	unsigned int indice = this->unHash->hashString(unaPalabra->getNombre());

	vector<Palabra*>::iterator it;
	it = this->palabras->begin();
	advance(it,indice);
	this->palabras->insert(it, unaPalabra);
}

Modelo0::~Modelo0() {
	delete[] this->palabras;
}

