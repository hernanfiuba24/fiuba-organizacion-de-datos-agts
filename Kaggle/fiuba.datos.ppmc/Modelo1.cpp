/*
 * Modelo1.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo1.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"

Modelo1::Modelo1(){
	this->contextos = new list<Contexto*>;

}

//CORREGIDO!!!
void Modelo1::agregarContexto(Contexto* unContexto){

	Palabra* unEscape = new Palabra("esc");
	unContexto->agregarPalabra(unEscape);

	this->contextos->push_back(unContexto);

}

Modelo1::~Modelo1() {
	//CONTROLAR ESTE DESTRUCTOR!!!!
//	for (list<Palabra*>::iterator it = this->contextos->begin(); it <= this->contextos->end();it++){
//		delete (*it);
//	}
	delete this->contextos;
}

