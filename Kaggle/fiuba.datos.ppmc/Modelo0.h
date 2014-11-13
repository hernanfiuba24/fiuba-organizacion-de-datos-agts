/*
 * Modelo0.h
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_PPMC_MODELO0_H_
#define FIUBA_DATOS_PPMC_MODELO0_H_

#include <vector>
#include "../fiuba.datos.hashing/HashingUniversalS.h"
#include "../fiuba.datos.ppmc/Palabra.h"

class Modelo0 {
public:
	Modelo0(int primo);
	void agregarPalabra(Palabra* unaPalabra);
	virtual ~Modelo0();

private:
	vector<Palabra*>* palabras;
	HashingUniversalS* unHash;
};

#endif /* FIUBA_DATOS_PPMC_MODELO0_H_ */
