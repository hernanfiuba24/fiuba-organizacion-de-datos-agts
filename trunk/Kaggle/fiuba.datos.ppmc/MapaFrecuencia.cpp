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
	this->hashFrecuencia = new map<unsigned long, Palabra*>;
}

map<unsigned long, Palabra* >* MapaFrecuencia::getHashFrecuencia(){
	return this->hashFrecuencia;
}

void MapaFrecuencia::incrementarFrecuencia(unsigned long clave){
	Palabra* unaPalabra = (*this->hashFrecuencia)[clave];
	unaPalabra->incrementarFrecuencia();
}

unsigned long MapaFrecuencia::getFrecuencia(unsigned long clave){
	//Palabra* unaPalabra = (*this->hashFrecuencia)[clave];
	map<unsigned long, Palabra*>::iterator iter = this->hashFrecuencia->find(clave);
	unsigned long frecuencia = (*iter).second->getFrecuencia();
	return frecuencia;
}

bool MapaFrecuencia::existeClave(unsigned long clave){
	map<unsigned long, Palabra*>::iterator iter = this->hashFrecuencia->find(clave);
	if ( iter  == this->hashFrecuencia->end())
		return false;
	string nombrepalabra = (*iter).second->getPalabra();
	unsigned long fre = (*iter).second->getFrecuencia();
	return true;
}

void MapaFrecuencia::agregarClave(unsigned long clave, string palabraAgregar){
	Palabra* unaPalabra = new Palabra(palabraAgregar);
	(*this->hashFrecuencia).insert( make_pair(clave, unaPalabra));
//	pair<string, unsigned long> palabraFrecuencia (palabraAgregar,1);
//	(*this->hashFrecuencia)[clave] = palabraFrecuencia;
}

