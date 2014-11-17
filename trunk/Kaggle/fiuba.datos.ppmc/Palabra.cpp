/*
 * Palabra.cpp
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#include "Palabra.h"
#include <iostream>

using namespace std;

Palabra::Palabra(string unNombre) {
	this->frecuencia = 1;
	this->nombre = unNombre;

}

void Palabra::incrementarFrecuencia(){
	this->frecuencia++;
}

string Palabra::getNombre(){
	return this->nombre;
}

bool Palabra::esIgualA(Palabra* unaPalabra){
	if(this->nombre == unaPalabra->getNombre())
		return true;
	return false;
}

