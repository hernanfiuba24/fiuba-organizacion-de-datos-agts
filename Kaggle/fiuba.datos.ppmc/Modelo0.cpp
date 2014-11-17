/*
 * Modelo0.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo0.h"

using namespace std;

Modelo0::Modelo0() {
	this->palabras = new list<Palabra*>;
}

void Modelo0::agregarPalabra(Palabra* unaPalabra){
	this->palabras->push_back(unaPalabra);
}

Modelo0::~Modelo0() {
	//CONTROLAR ESTE DESTRUCTOR!!!!
//	for (list<Palabra*>::iterator it = this->palabras->begin(); it <= this->palabras->end();it++){
//		delete (*it);
//	}
	delete this->palabras;
}

