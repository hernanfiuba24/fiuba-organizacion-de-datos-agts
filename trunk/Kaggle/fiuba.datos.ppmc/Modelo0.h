/*
 * Modelo0.h
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include <vector>
#include "Palabra.h"

#ifndef FIUBA_DATOS_PPMC_MODELO0_H_
#define FIUBA_DATOS_PPMC_MODELO0_H_

class Modelo0 {
public:
	Modelo0();
	void agregarPalabra(Palabra* unaPalabra);
	virtual ~Modelo0();

private:
	vector<Palabra*>* palabras;
};

#endif /* FIUBA_DATOS_PPMC_MODELO0_H_ */
