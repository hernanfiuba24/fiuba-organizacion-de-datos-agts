/*
 * Modelo0.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo0.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"
#include "../fiuba.datos.ppmc/Palabra.h"

using namespace std;

Modelo0::Modelo0() {
	this->palabras = new vector<Palabra*>;

	//Agrego el escape al modelo0
	Palabra* escape = new Palabra("esc");
	this->palabras->push_back(escape);
}

//Se hashea la palabra para facilitar el ingreso de una palabra nueva
void Modelo0::agregarPalabra(Palabra* unaPalabra){
	int primo = 5001;
	HashingUniversalS* unHash = new HashingUniversalS(primo);
	unsigned int indice = unHash->hashString(unaPalabra->getNombre());

	vector<Palabra*>::iterator it;
	it = this->palabras->begin();
	advance(it,indice);
	this->palabras->insert(it, unaPalabra);
}

Modelo0::~Modelo0() {
	delete[] this->palabras;
}

