/*
 * Modelo1.h
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */


#ifndef MODELO1_H_
#define MODELO1_H_

#include <list>
#include "Contexto.h"

class Modelo1 {
public:
	Modelo1();
	void agregarContexto(Contexto* unContexto);
	Contexto* devolverContexto(Contexto* unContexto);
	virtual ~Modelo1();

private:
	std::list<Contexto*>* contextos;
};

#endif /* MODELO1_H_ */
