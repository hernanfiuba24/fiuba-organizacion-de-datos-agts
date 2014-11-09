/*
 * Modelo.h
 *
 *  Created on: 19/10/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_PPMC_MODELO_H_
#define FIUBA_DATOS_PPMC_MODELO_H_

#include <list>
#include "Contexto.h"

using namespace std;

class Modelo {
private:
	list<Contexto>* contextos;
	int numeroDeModelo;

public:
	Modelo(int numeroDeModelo);
	void agregarContexto(Contexto unContexto);
	~Modelo();

};

#endif /* FIUBA_DATOS_PPMC_MODELO_H_ */
#endif /* FIUBA_DATOS_PPMC_MODELO_H_ */
