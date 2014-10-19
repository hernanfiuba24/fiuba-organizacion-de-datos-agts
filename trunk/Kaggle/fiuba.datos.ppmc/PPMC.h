/*
 * PPMC.h
 *
 *  Created on: 18/10/2014
 *      Author: ezequiel
 */
#ifndef FIUBA_DATOS_PPMC_PPMC_H_
#define FIUBA_DATOS_PPMC_PPMC_H_

#include <list>
#include <iostream>

using namespace std;

class PPMC {
private:
	list<Modelo> modelos;

public:
	PPMC(int cantidadDeModelos);
	~PPMC();
};

#endif
