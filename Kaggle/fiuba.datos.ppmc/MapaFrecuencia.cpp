/*
 * Palabra.cpp
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#include "MapaFrecuencia.h"

using namespace std;

MapaFrecuencia::MapaFrecuencia() {
	this->hashFrecuencia = new map<unsigned long, pair<string, unsigned> >;
}

map<unsigned long, pair<string, unsigned> >* MapaFrecuencia::getHashFrecuencia(){
	return this->hashFrecuencia;
}

void MapaFrecuencia::incrementarFrecuencia(unsigned long clave){
	(*this->hashFrecuencia)[clave].second++;
}

unsigned MapaFrecuencia::getFrecuencia(unsigned long clave){
	//pair<string, unsigned> unPair = (*this->hashFrecuencia)[clave];
	//return unPair.second;
	map<unsigned long, pair<string, unsigned> >::iterator iterMapFrec = this->hashFrecuencia->find(clave);
	return (*iterMapFrec).second.second;
}

bool MapaFrecuencia::existeClave(unsigned long clave){
	if (this->hashFrecuencia->find(clave) == this->hashFrecuencia->end())
		return false;
	return true;
}

void MapaFrecuencia::agregarClave(unsigned long clave, string palabraAgregar){
	pair<string, unsigned> palabraFrecuencia (palabraAgregar,1);
	(*this->hashFrecuencia)[clave] = palabraFrecuencia;
}

