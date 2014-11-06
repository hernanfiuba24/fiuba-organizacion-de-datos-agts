/*
 * Palabra.cpp
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#include "Palabra.h"
#include <iostream>

Palabra::Palabra(std::string unNombre) {
	this->frecuencia = 1;
	this->nombre = unNombre;

}

Palabra::~Palabra() {
	// TODO Auto-generated destructor stub
}
void Palabra::incrementarFrecuencia(){
	this->frecuencia++;
}

