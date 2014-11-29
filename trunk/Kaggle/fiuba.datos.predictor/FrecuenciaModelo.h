/*
 * FrecuenciaModelo.h
 *
 *  Created on: 29/11/2014
 *      Author: hernan
 */

#ifndef FIUBA_DATOS_PREDICTOR_FRECUENCIAMODELO_H_
#define FIUBA_DATOS_PREDICTOR_FRECUENCIAMODELO_H_

class FrecuenciaModelo {
public:
	FrecuenciaModelo();
	FrecuenciaModelo(unsigned long unaFrecuencia, unsigned unModelo);
	void setFrecuencia(unsigned long unFecuencia);
	void setModelo(unsigned unModelo);
	unsigned long getFrecuencia();
	unsigned getModelo();
	virtual ~FrecuenciaModelo();
private:
	 unsigned long frecuencia;
	 unsigned modelo;
};

#endif /* FIUBA_DATOS_PREDICTOR_FRECUENCIAMODELO_H_ */
