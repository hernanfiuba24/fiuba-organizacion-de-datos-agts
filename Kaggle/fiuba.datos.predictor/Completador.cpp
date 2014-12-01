/*
 * Completador.cpp
 *
 *  Created on: 1/12/2014
 *      Author: hernan
 */

#include "Completador.h"

using namespace std;

Completador::Completador(unsigned unNumeroModelo, unsigned unIndex, unsigned unNumeroFrase, string unaPalabraConMayorFrecuencia){

	this->numeroFrase = unNumeroFrase;
	this->numeroModelo = unNumeroModelo;
	this->index = unIndex;
	this->palabraConMayorFrecuencia = unaPalabraConMayorFrecuencia;
}

unsigned Completador::getNumeroFrase(){
	return this->numeroFrase;
}

unsigned Completador::getIndex(){
	return this->index;
}

unsigned Completador::getNumeroModelo(){
	return this->numeroModelo;
}

Completador::~Completador() {
	// TODO Auto-generated destructor stub
}
