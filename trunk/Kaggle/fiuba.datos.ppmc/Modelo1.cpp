/*
 * Modelo1.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo1.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"

using namespace std;

Modelo1::Modelo1(){
	this->contextos = new list<Contexto*>;

}

//CORREGIDO!!!
void Modelo1::agregarContexto(Contexto* unContexto){

	Contexto* contextoExistente = this->devolverContexto(unContexto);
		if (contextoExistente != NULL){
			contextoExistente->agregarPalabra(unContexto->devolverPrimeraPalabra());
		}
		else{
			Palabra* unEscape = new Palabra("esc");
			unContexto->agregarPalabra(unEscape);
			this->contextos->push_back(unContexto);
		}
	}

Contexto* Modelo1::devolverContexto(Contexto* unContexto){

	list<Contexto*>::iterator it = this->contextos->begin();
	Contexto* contextoExistente;
	bool contextoEncontrado = false;
	while( (it != this->contextos->end()) || !(contextoEncontrado)){
		contextoExistente = (*it);
		contextoEncontrado = contextoExistente->esIgualA(unContexto);
	}
	if (contextoEncontrado)
		return contextoExistente;
	else
		return NULL;
}

Modelo1::~Modelo1() {
	//CONTROLAR ESTE DESTRUCTOR!!!!
//	for (list<Palabra*>::iterator it = this->contextos->begin(); it <= this->contextos->end();it++){
//		delete (*it);
//	}
	delete this->contextos;
}

