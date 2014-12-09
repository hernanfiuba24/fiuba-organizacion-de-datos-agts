/*
 * FrecuenciaModelo.cpp
 *
 *  Created on: 29/11/2014
 *      Author: hernan
 */

#include "FrecuenciaModelo.h"

using namespace std;

FrecuenciaModelo::FrecuenciaModelo(float unaFrecuencia, string unaPalabra){
	this->frecuencia = unaFrecuencia;
	this->palabraConMayorFrec = unaPalabra;
}

void FrecuenciaModelo::setFrecuencia(float unaFrecuencia){
	this->frecuencia += unaFrecuencia;
}

float FrecuenciaModelo::getFrecuencia(){
	return this->frecuencia;
}

string FrecuenciaModelo::getPalabraConMayorFrecuencia(){
	return this->palabraConMayorFrec;
}

void FrecuenciaModelo::setearPalabraConMayorFrecuencia(string unaPalabra){
	this->palabraConMayorFrec = unaPalabra;
}

FrecuenciaModelo::~FrecuenciaModelo() {
	// TODO Auto-generated destructor stub
}

