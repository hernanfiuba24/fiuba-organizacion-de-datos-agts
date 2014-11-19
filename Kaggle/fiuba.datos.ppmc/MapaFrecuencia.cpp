/*
 * Palabra.cpp
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#include "MapaFrecuencia.h"

#include <iostream>

using namespace std;

MapaFrecuencia::MapaFrecuencia() {
}

void MapaFrecuencia::incrementarFrecuencia(unsigned clave){
	this->hashFrecuencia[clave]++;
}

unsigned MapaFrecuencia::getFrecuencia(unsigned clave){
	return this->hashFrecuencia[clave];
}

/*bool MapaFrecuencia::esIgualA(Palabra* unaPalabra){
	if(this->nombre == unaPalabra->getNombre())
		return true;
	return false;
}*/

