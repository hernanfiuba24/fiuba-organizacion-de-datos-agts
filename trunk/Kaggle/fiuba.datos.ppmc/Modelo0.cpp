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
}

MapaFrecuencia* Modelo0::getMapaFrecuencia(){
	return this->unMapa;
}

void Modelo0::agregarPalabra(string unNombre){

	unsigned long clave = this->unHash->hashearConMod(unNombre);

	if (this->unMapa->existeClave(clave))
		this->unMapa->incrementarFrecuencia(clave);
	else
		this->unMapa->agregarClave(clave, unNombre);

}

float Modelo0::devolverPenalizacion(){
	return 0.0256;
}

Jenkins* Modelo0::getJenkins(){
	return this->unHash;
}

Modelo0::~Modelo0() {
	//CONTROLAR ESTE DESTRUCTOR!!!!
//	for (list<Palabra*>::iterator it = this->palabras->begin(); it <= this->palabras->end();it++){
//		delete (*it);
//	}
	delete this->unMapa;
}

