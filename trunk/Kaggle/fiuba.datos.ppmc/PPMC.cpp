/*
 * PPMC.cpp
 *
 *  Created on: 18/10/2014
 *      Author: ezequiel
 */

#include "PPMC.h"
#include "Modelo.h"

PPMC::PPMC(int cantidadDeModelos) {
	for(int i = 0; i<=cantidadDeModelos; i++){
		Modelo modeloi = new Modelo(i);
		this->modelos.push_back(modeloi);
	}
}

PPMC::~PPMC() {
	// Borrar lista generada en el constructor
}

