/*
 * FrecuenciaModelo.cpp
 *
 *  Created on: 29/11/2014
 *      Author: hernan
 */

#include "FrecuenciaModelo.h"

using namespace std;

FrecuenciaModelo::FrecuenciaModelo(){}

FrecuenciaModelo::FrecuenciaModelo(float unaFrecuencia, unsigned unModelo){
	this->frecuencia = unaFrecuencia;
	this->modelo = unModelo;
}

void FrecuenciaModelo::setFrecuencia(float unaFrecuencia){
	this->frecuencia += unaFrecuencia;
}

void FrecuenciaModelo::setModelo(unsigned unModelo){
	if (this->modelo < unModelo)
		this->modelo = unModelo;
}

float FrecuenciaModelo::getFrecuencia(){
	return this->frecuencia;
}

unsigned FrecuenciaModelo::getModelo(){
	return this->modelo;
}

bool FrecuenciaModelo::esMayorElModelo(unsigned numeroModelo){
	return (numeroModelo>this->modelo);
}

void FrecuenciaModelo::setearPalabraConMayorFrecuencia(string unaPalabra){
	this->palabraConMayorFrec = unaPalabra;
}

FrecuenciaModelo::~FrecuenciaModelo() {
	// TODO Auto-generated destructor stub
}

