/*
 * Modelo.cpp
 *
 *  Created on: 19/10/2014
 *      Author: ezequiel
 */

#include "Modelo.h"

Modelo::Modelo(int numeroDeModelo){
	if (numeroDeModelo == 0){
		Contexto contexto0 = new Contexto();
	}
	else{
		Contexto contextoMayor = new Contexto(numeroDeModelo);
		}

}

Modelo::~Modelo() {
	// TODO Auto-generated destructor stub
}

