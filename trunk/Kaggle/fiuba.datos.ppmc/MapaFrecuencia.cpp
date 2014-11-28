/*
 * Palabra.cpp
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#include "MapaFrecuencia.h"

using namespace std;

MapaFrecuencia::MapaFrecuencia() {
	this->hashFrecuencia = new map<unsigned long, pair<string, unsigned long> >;
}

map<unsigned long, pair<string, unsigned long> >* MapaFrecuencia::getHashFrecuencia(){
	return this->hashFrecuencia;
}

void MapaFrecuencia::incrementarFrecuencia(unsigned long clave){
	(*this->hashFrecuencia)[clave].second++;
}

unsigned long MapaFrecuencia::getFrecuencia(unsigned long clave){
	//pair<string, unsigned> unPair = (*this->hashFrecuencia)[clave];
	//return unPair.second;
	map<unsigned long, pair<string, unsigned long> >::iterator iterMapFrec = this->hashFrecuencia->find(clave);
	return (*iterMapFrec).second.second;
}

bool MapaFrecuencia::existeClave(unsigned long clave){
	if (this->hashFrecuencia->find(clave) == this->hashFrecuencia->end())
		return false;
	return true;
}

void MapaFrecuencia::agregarClave(unsigned long clave, string palabraAgregar){
	pair<string, unsigned long> palabraFrecuencia (palabraAgregar,1);
	(*this->hashFrecuencia)[clave] = palabraFrecuencia;
}

