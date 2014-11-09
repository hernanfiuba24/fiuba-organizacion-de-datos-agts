/*
 * Modelo.cpp
 *
 *  Created on: 19/10/2014
 *      Author: ezequiel
 */

#include "Modelo.h"

Modelo::Modelo(int numeroDeModelo){
	this->contextos = new list<Contexto>;
	this->numeroDeModelo = numeroDeModelo;
}

Modelo::~Modelo() {
	// TODO Auto-generated destructor stub
}
void Modelo::agregarContexto(Contexto unContexto){
	std::list<Contexto>::iterator it;
	it = this->contextos->begin();
    it++;
 	this->contextos->insert(it, unContexto);

}
