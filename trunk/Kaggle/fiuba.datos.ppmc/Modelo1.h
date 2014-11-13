/*
 * Modelo1.h
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */


#ifndef MODELO1_H_
#define MODELO1_H_

#include <vector>
#include "Contexto.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"

class Modelo1 {
public:
	Modelo1(int primo);
	void agregarContexto(Contexto* unContexto);
	virtual ~Modelo1();

private:
	vector<Contexto*>* contextos;
	HashingUniversalS* unHash;
};

#endif /* MODELO1_H_ */
