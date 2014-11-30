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

void Modelo0::setMapaFrecuencia(unsigned long hash, Palabra* palabra){
	return this->unMapa->agregarClave(hash, palabra->getPalabra());
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

unsigned long Modelo0::hashearPalabra(string palabra){
	return this->unHash->hashearConMod(palabra);
}

unsigned long Modelo0::devolverFrecuencia(string palabra){
	unsigned long clavePalabra =
					this->hashearPalabra(palabra);
	bool existePalabra = this->unMapa->existeClave(clavePalabra);
	if (existePalabra)
		this->unMapa->getFrecuencia(clavePalabra);
}

Modelo0::~Modelo0() {
	delete this->unMapa;
}

