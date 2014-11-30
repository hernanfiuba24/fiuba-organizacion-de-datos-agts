/*
 * Frase.cpp
 *
 *  Created on: 30/11/2014
 *      Author: ezequiel
 */

#include "Frase.h"

using namespace std;

Frase::Frase(vector< string >* unaFrase){
	this->fraseACompletar = unaFrase;
	this->frecuencias = new vector<FrecuenciaModelo* >;

	this->frecuencias->resize(this->fraseACompletar->size());
	this->inicializarFrecuencias();

	this->indiceDondeCompletar = 0;
}

void Frase::inicializarFrecuencias(){
	unsigned tam = this->frecuencias->size();
	for (unsigned i = 0; i < frecuencias->size(); i++) {
		FrecuenciaModelo *unFrecMod = new FrecuenciaModelo(0, NULL);
		(*frecuencias)[i] = unFrecMod;
	}
}

string Frase::devolverContexto(int numeroModelo, int inicio){

	unsigned indice = inicio-1;

	string contexto = (*this->fraseACompletar)[indice];
	indice--;
	for(indice;indice>=(inicio-numeroModelo);indice--){
		contexto = (*this->fraseACompletar)[indice] + " " + contexto;
	}
	return contexto;
}

string Frase::devolverPalabra(unsigned index){
	string palabra = (*this->fraseACompletar)[index];
	return palabra;
}

unsigned Frase::getTamanioFrase(){
	return this->fraseACompletar->size();
}

void Frase::setFrecuencia(float penalizacion, unsigned long frecuencia, unsigned numeroModelo, unsigned index){
	(*this->frecuencias)[numeroModelo + index]->setFrecuencia(penalizacion*frecuencia);
}

void Frase::setModelo(unsigned numeroModelo, unsigned index){
	(*this->frecuencias)[numeroModelo + index]->setModelo(numeroModelo);
}

unsigned Frase::getModelo(unsigned numeroModelo, unsigned index){

	return (*this->frecuencias)[numeroModelo + index]->getModelo();

}


Frase::~Frase() {
	// TODO Auto-generated destructor stub
}

