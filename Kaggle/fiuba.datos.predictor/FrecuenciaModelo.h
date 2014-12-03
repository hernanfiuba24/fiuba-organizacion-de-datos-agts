/*
 * FrecuenciaModelo.h
 *
 *  Created on: 29/11/2014
 *      Author: hernan
 */

#ifndef FIUBA_DATOS_PREDICTOR_FRECUENCIAMODELO_H_
#define FIUBA_DATOS_PREDICTOR_FRECUENCIAMODELO_H_

#include <string>

class FrecuenciaModelo {
public:
	FrecuenciaModelo(float unaFrecuencia, std::string unaPalabra);
	void setFrecuencia(float unaFrecuencia);
	//void setModelo(unsigned unModelo);
	float getFrecuencia();
	//unsigned getModelo();
	std::string getPalabraConMayorFrecuencia();
	//bool esMayorElModelo(unsigned numeroModelo);
	void setearPalabraConMayorFrecuencia(std::string unaPalabraConMayorFrecuencia);
	virtual ~FrecuenciaModelo();
private:
	 float frecuencia;
	 //unsigned modelo;
	 std::string palabraConMayorFrec;
};

#endif /* FIUBA_DATOS_PREDICTOR_FRECUENCIAMODELO_H_ */
