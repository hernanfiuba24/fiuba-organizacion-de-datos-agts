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
	Modelo1(unsigned primo);
	void agregarContexto(std::string nombreContexto, std::string nombrePalabra, int numeroModelo);
	//Contexto* devolverContexto(Contexto* unContexto);
	virtual ~Modelo1();

private:
	//std::vector<Contexto*>* contextos;
	MapaContexto *contextos;
	Jenkins *unHash;

};

#endif /* MODELO1_H_ */
