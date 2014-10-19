/*
 * Contexto.cpp
 *
 *  Created on: 19/10/2014
 *      Author: ezequiel
 */

#include "Contexto.h"

Contexto::Contexto() {
	this->contexto = NULL;
	this->palabrasFrecuencias = new map();
	this->agregarPalabra((string)'escape');

}

//ESTO HAY QUE CAMBIARLO, HACEN LO MISMO!!!!
//LO QUE QUIERO HACER ES TRATAR DE DIFERNCIAR EL MODELO 0 DEL RESTO
//PORQUE SE QUE EN EL MODELO 0 EL CONTEXTO ES NULL

Contexto::Contexto(int numeroModelo){
	this->contexto = NULL;
	this->palabrasFrecuencias = new map();
	this->agregarPalabra((string)'escape');
}

void Contexto::agregarPalabra(string unaPalabra){
	this->palabrasFrecuencias.insert(palabraFrecuencia(unaPalabra, 1));
}

Contexto::~Contexto() {
	// TODO Auto-generated destructor stub
}

