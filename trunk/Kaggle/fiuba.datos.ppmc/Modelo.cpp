/*
 * Modelo.cpp
 *
 *  Created on: 19/10/2014
 *      Author: ezequiel
 */

#include "Modelo.h"
#include "HashingUniversalS.h"

Modelo::Modelo(int numeroDeModelo){
	this->contextos = new list<Contexto>;
	this->numeroDeModelo = numeroDeModelo;
}

Modelo::~Modelo() {
	delete this->contextos;
}
void Modelo::agregarContexto(Contexto unContexto){
	this->hashearContexto(unContexto);

	std::list<Contexto>::iterator it;
	it = this->contextos->begin();
    it++;
 	this->contextos->insert(it, unContexto);
}

int Modelo::hashearContexto(Contexto unContexto){
	if (this->numeroDeModelo = 2)
		HashingUniversalS unHash = new HashingUniversalS(3001);
	else if (this->numeroDeModelo = 3)
		HashingUniversalS unHash = new HashingUniversalS(6001);
	else if (this->numeroDeModelo = 4)
		HashingUniversalS unHash = new HashingUniversalS(7001);
	else if (this->numeroDeModelo = 5)
		HashingUniversalS unHash = new HashingUniversalS(8001); //ES POCO ESPACIO. 8001 SON MENOS DE 150K (SE PUDE AGREGAR MUCHO MAS)

	unHash.hashString(unContexto.);
}
