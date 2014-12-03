/*
 * Modelo1.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo1.h"

using namespace std;

Modelo1::Modelo1(unsigned long primo, int numeroModelo){

	//this->contextos = new vector<Contexto*>;
	//CAMBIAR ESTE VALOR POR UN PRIMO AJUSTABLE AL MODELO
	this->unHash = new Jenkins(primo);
	this->contextos = new MapaContexto();
	this->numeroModelo = numeroModelo;

}

//CORREGIDO!!!
void Modelo1::agregarContexto(string nombreContexto, string nombrePalabra){

	unsigned clave = this->unHash->hashearConMod(nombreContexto);
	bool existeClave = this->contextos->existeClave(clave);
	if (existeClave)
		this->contextos->agregarContextoExistente(clave, nombrePalabra);
	else
		this->contextos->agregarContexto(clave, nombrePalabra, this->numeroModelo);

}

MapaContexto* Modelo1::getMapa(){
	return this->contextos;
}


Jenkins* Modelo1::getJenkins(){
	return this->unHash;
}


float Modelo1::devolverPenalizacion(){
	return 0.064;
}

unsigned long Modelo1::hashearContexto(string contextoAHashear){

	return this->unHash->hashearConMod(contextoAHashear);
}

bool Modelo1::existeContexto(unsigned long claveContexto){

	return this->contextos->existeClave(claveContexto);
}

unsigned long Modelo1::hashearPalabra(unsigned long claveContexto, string palabraActual){
	return this->contextos->hashearPalabra(claveContexto, palabraActual);
}

bool Modelo1::existePalabraEnContexto(unsigned long claveContexto, unsigned long clavePalabra){
	Contexto* contexto = this->contextos->getContextos(claveContexto);
	return contexto->existePalabra(clavePalabra);
}

pair<unsigned long, bool>* Modelo1::devolverFrecuencia(string nombreContexto, string nombrePalabra){
	pair<unsigned long, bool >* frecExisteContexto = new pair<unsigned long, bool>;
	frecExisteContexto->first = 0;
	frecExisteContexto->second = false;
	unsigned long claveContexto = this->hashearContexto(nombreContexto);

	bool existeContexto = this->existeContexto(claveContexto);
	frecExisteContexto->second = existeContexto;
	if (existeContexto) {
		unsigned long clavePalabra =
				this->hashearPalabra(claveContexto, nombrePalabra);
		bool existePalabraEnContexto =
				this->existePalabraEnContexto(claveContexto, clavePalabra);
		if (existePalabraEnContexto) {
			frecExisteContexto->first = this->contextos->getFrecuencia(claveContexto, clavePalabra);
		}
	}
	return frecExisteContexto;
}

string Modelo1::devolverPalabraConMayorFrecuencia(string contexto){
	unsigned long clave = this->unHash->hashearConMod(contexto);
	Contexto *unContexto = this->contextos->getContextos(clave);

	string palabraConMayorFrecuencia = unContexto->devolverPalabraConMayorFrecuencia();
	return palabraConMayorFrecuencia;
}

Modelo1::~Modelo1() {
	delete this->contextos;
	delete this->unHash;
}

