/*
 * Modelo1.h
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */


#ifndef MODELO1_H_
#define MODELO1_H_

//#include <vector>
#include "Contexto.h"
#include "../fiuba.datos.hashing/Jenkins.h"
#include "../fiuba.datos.ppmc/MapaContexto.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"

class Modelo1 {
public:
	Modelo1(unsigned long primo, int numeroModelo);
	void agregarContexto(std::string nombreContexto, std::string nombrePalabra);
	//Contexto* devolverContexto(Contexto* unContexto);
	float devolverPenalizacion();
	virtual ~Modelo1();

private:
	//std::vector<Contexto*>* contextos;
	MapaContexto *contextos;
	Jenkins *unHash;
	int numeroModelo;

};

#endif /* MODELO1_H_ */
