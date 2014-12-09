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

void MapaFrecuencia::setFrecuencia(unsigned long clave, unsigned long frecuencia){
	map<unsigned long, Palabra*>::iterator iter = this->hashFrecuencia->find(clave);
	(*iter).second->setFrecuencia(frecuencia);
}

bool MapaFrecuencia::existeClave(unsigned long clave){
	map<unsigned long, Palabra*>::iterator iter = this->hashFrecuencia->find(clave);
	if ( iter  == this->hashFrecuencia->end())
		return false;
	return true;
}

void MapaFrecuencia::agregarClave(unsigned long clave, string palabraAgregar){
	Palabra* unaPalabra = new Palabra(palabraAgregar);
	(*this->hashFrecuencia).insert( make_pair(clave, unaPalabra));
//	pair<string, unsigned long> palabraFrecuencia (palabraAgregar,1);
//	(*this->hashFrecuencia)[clave] = palabraFrecuencia;
}


void MapaFrecuencia::agregarClave(unsigned long hashPalabra, Palabra* palabraAgregar){
	(*this->hashFrecuencia).insert( make_pair(hashPalabra, palabraAgregar));
}

string MapaFrecuencia::devolverPalabraConMayorFrecuencia(){
	unsigned index = 0;
	Palabra *palabraTemporal;
	string 	nombrePalabraMayorFrec;
	unsigned long frecuenciaTemporal;
	unsigned long frecuenciaMaxima = 0;

	map<unsigned long, Palabra*>::const_iterator iterFin =
					this->hashFrecuencia->end();
	for (map<unsigned long, Palabra*>::const_iterator iter =
				this->hashFrecuencia->begin(); iter != iterFin; ++iter){
			palabraTemporal = iter->second;
			frecuenciaTemporal = palabraTemporal->getFrecuencia();
			if(frecuenciaMaxima < frecuenciaTemporal){
				nombrePalabraMayorFrec = palabraTemporal->getPalabra();
				frecuenciaMaxima = frecuenciaTemporal;
			}
	}
	return nombrePalabraMayorFrec;
}

MapaFrecuencia::~MapaFrecuencia(){
	map<unsigned long, Palabra*>::iterator iterFin = this->hashFrecuencia->end();
	for(map<unsigned long, Palabra*>::iterator iter = this->hashFrecuencia->begin(); iter != iterFin; iter++)
		delete iter->second;
	delete this->hashFrecuencia;
}
