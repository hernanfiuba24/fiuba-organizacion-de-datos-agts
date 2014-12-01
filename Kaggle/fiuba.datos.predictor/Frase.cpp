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
	this->tamanioFrecuencias = this->fraseACompletar->size();
	this->frecuencias->resize(this->tamanioFrecuencias);
	this->inicializarFrecuencias();

	this->indiceDondeCompletar = 0;
}

void Frase::inicializarFrecuencias(){
	for (unsigned i = 0; i < this->tamanioFrecuencias; i++) {
		FrecuenciaModelo *unFrecMod = new FrecuenciaModelo(0, NULL);
		(*frecuencias)[i] = unFrecMod;
	}
}

string Frase::devolverContexto(int numeroModelo, int inicio){

	int indice = inicio-1;

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

Completador* Frase::devolverFrecuenciaMinima(unsigned numeroFrase){

	unsigned numeroModelo = (*this->frecuencias)[1]->getModelo();
	float menorFrecuencia = (*this->frecuencias)[1]->getFrecuencia();
	float frecTemporal;
	string palabraConMayorFrecuencia;
	for(unsigned index = 2; index < this->tamanioFrecuencias; index++){

		frecTemporal = (*this->frecuencias)[index]->getFrecuencia();
		if (menorFrecuencia > frecTemporal){
			menorFrecuencia = frecTemporal;
			numeroModelo = (*this->frecuencias)[index]->getModelo();
			//labraConMayorFrecuencia = (*this->frecuencias)[index]
		}
	}
	Completador* unComp = new Completador(numeroModelo, menorFrecuencia, numeroFrase, palabraConMayorFrecuencia);
	return unComp;
}

unsigned Frase::getModelo(unsigned numeroModelo, unsigned index){

	return (*this->frecuencias)[numeroModelo + index]->getModelo();

}

void Frase::setPalabraConMayorFrecuencia(ModelosSuperiores* modelosSuperiores,std::string contexto, unsigned index, unsigned numeroModelo){
	string palabraConMayorFrecuencia;
	FrecuenciaModelo *unaFrecuenciaModelo = (*this->frecuencias)[numeroModelo+index];
	bool hayQueAgregarPalabra;
	hayQueAgregarPalabra = unaFrecuenciaModelo->esMayorElModelo(numeroModelo);
	if (hayQueAgregarPalabra){
		palabraConMayorFrecuencia = this->buscarPalabraConMayorFrecuencia(modelosSuperiores, contexto);
		(*this->frecuencias)[numeroModelo+index]->setearPalabraConMayorFrecuencia(palabraConMayorFrecuencia);
	}
}

string Frase::buscarPalabraConMayorFrecuencia(ModelosSuperiores *modelosSuperiores, std::string contexto){
	string palabraMayorFrec = modelosSuperiores->devolverPalabraConMayorFrecuencia(contexto);
	return palabraMayorFrec;
}
Frase::~Frase() {
	// TODO Auto-generated destructor stub
}

