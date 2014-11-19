/*
 * Palabra.cpp
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#include "MapaFrecuencia.h"

using namespace std;

MapaFrecuencia::MapaFrecuencia() {
	this->hashFrecuencia = new map<unsigned, unsigned>;
}

void MapaFrecuencia::incrementarFrecuencia(unsigned clave){
	(this->hashFrecuencia[clave])++;
}

unsigned MapaFrecuencia::getFrecuencia(unsigned clave){
	return this->hashFrecuencia[clave];
}

bool MapaFrecuencia::existeClave(unsigned clave){
	if (this->hashFrecuencia->find(clave) == this->hashFrecuencia->end())
		return false;
	return true;
}

void MapaFrecuencia::agregarClave(unsigned clave){
	(*this->hashFrecuencia)[clave] = 1;
}

/*bool MapaFrecuencia::esIgualA(Palabra* unaPalabra){
	if(this->nombre == unaPalabra->getNombre())
		return true;
	return false;
}*/

