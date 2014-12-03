/*
 * Completador.cpp
 *
 *  Created on: 1/12/2014
 *      Author: hernan
 */

#include "Completador.h"

using namespace std;

Completador::Completador(unsigned unaPos, unsigned unNumeroFrase, string unaPalabraConMayorFrecuencia){

	this->numeroFrase = unNumeroFrase;
	this->posEnDondeCompletarFrase = unaPos;
	this->palabraConMayorFrecuencia = unaPalabraConMayorFrecuencia;
}

unsigned Completador::getNumeroFrase(){
	return this->numeroFrase;
}

unsigned Completador::getPosEnDondeCompletarFrase(){
	return this->posEnDondeCompletarFrase;
}

string Completador::getPalabraConMayorFrecuencia(){
	return this->palabraConMayorFrecuencia;
}

Completador::~Completador() {
	// TODO Auto-generated destructor stub
}
