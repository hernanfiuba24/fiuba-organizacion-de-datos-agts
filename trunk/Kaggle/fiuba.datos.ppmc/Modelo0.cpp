/*
 * Modelo0.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo0.h"

using namespace std;

Modelo0::Modelo0(unsigned long primo){
	this->unHash = new Jenkins(primo);
	this->unMapa = new MapaFrecuencia();
	//this->palabras = new vector<Palabra*>;
}

MapaFrecuencia* Modelo0::getMapaFrecuencia(){
	return this->unMapa;
}

void Modelo0::agregarPalabra(string unNombre){

	unsigned clave = this->unHash->hashearConMod(unNombre);

	if (this->unMapa->existeClave(clave))
		this->unMapa->incrementarFrecuencia(clave);
	else
		this->unMapa->agregarClave(clave);

}

Modelo0::~Modelo0() {
	//CONTROLAR ESTE DESTRUCTOR!!!!
//	for (list<Palabra*>::iterator it = this->palabras->begin(); it <= this->palabras->end();it++){
//		delete (*it);
//	}
	delete this->unMapa;
}

