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

Modelo1::~Modelo1() {
	//CONTROLAR ESTE DESTRUCTOR!!!!
//	for (list<Palabra*>::iterator it = this->contextos->begin(); it <= this->contextos->end();it++){
//		delete (*it);
//	}
	delete this->contextos;
	delete this->unHash;
}

