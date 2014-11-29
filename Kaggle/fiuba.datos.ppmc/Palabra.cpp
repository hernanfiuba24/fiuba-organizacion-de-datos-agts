/*
 * Palabra.cpp
 *
 *  Created on: 28/11/2014
 *      Author: ezequiel
 */

#include "Palabra.h"

using namespace std;

Palabra::Palabra(string unaPalabra){
	this->palabra = unaPalabra;
	this->frecuencia = 1;
}

unsigned long Palabra::getFrecuencia(){
	return this->frecuencia;
}

void Palabra::setFrecuencia(int frecuencia){
	this->frecuencia = frecuencia;
}

string Palabra::getPalabra(){
	return this->palabra;
}

void Palabra::incrementarFrecuencia(){
	this->frecuencia++;
}

void Palabra::inicializarPalabra(string unaPalabra){
	this->palabra = unaPalabra;
	this->frecuencia = 1;
}
