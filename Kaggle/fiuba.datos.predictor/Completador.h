/*
 * Completador.h
 *
 *  Created on: 1/12/2014
 *      Author: hernan
 */

#ifndef FIUBA_DATOS_PREDICTOR_COMPLETADOR_H_
#define FIUBA_DATOS_PREDICTOR_COMPLETADOR_H_

#include <string>

class Completador {
public:
	Completador(unsigned unNumeroModelo, unsigned unIndex, unsigned unNumeroFrase, std::string unaPConMayorFrecuencia);
	unsigned getNumeroModelo();
	unsigned getPosEnDondeCompletarFrase();
	unsigned getNumeroFrase();
	std::string getPalabraConMayorFrecuencia();
	virtual ~Completador();
private:
	unsigned numeroFrase;
	unsigned posEnDondeCompletarFrase;
	unsigned numeroModelo;
	std::string palabraConMayorFrecuencia;
};


#endif /* FIUBA_DATOS_PREDICTOR_COMPLETADOR_H_ */
