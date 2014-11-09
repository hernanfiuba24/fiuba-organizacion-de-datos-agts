/*
 * Modelo1.h
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include <vector>
#include "Contexto.h"

#ifndef MODELO1_H_
#define MODELO1_H_

class Modelo1 {
public:
	Modelo1();
	void agregarContexto(Contexto unContexto);
	virtual ~Modelo1();

private:
	vector<Contexto>* contextos;
};

#endif /* MODELO1_H_ */
