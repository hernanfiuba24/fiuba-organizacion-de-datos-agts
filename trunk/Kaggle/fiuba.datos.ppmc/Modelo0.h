/*
 * Modelo0.h
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_PPMC_MODELO0_H_
#define FIUBA_DATOS_PPMC_MODELO0_H_

#include <vector>
#include "../fiuba.datos.ppmc/Palabra.h"
#include "../fiuba.datos.hashing/Jenkins.h"


class Modelo0 {
public:
	Modelo0(unsigned primo);
	void agregarPalabra(Palabra* unaPalabra);
	Palabra* devolverPalabra(Palabra* unaPalabra);
	virtual ~Modelo0();

private:
	Jenkins* unHash;
	std::map<unsigned*, unsigned*> hashFrecuencia;
	//std::vector<Palabra*>* palabras;
};

#endif /* FIUBA_DATOS_PPMC_MODELO0_H_ */
