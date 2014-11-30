/*
 * Frase.h
 *
 *  Created on: 30/11/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_PREDICTOR_FRASE_H_
#define FIUBA_DATOS_PREDICTOR_FRASE_H_

#include "../fiuba.datos.predictor/FrecuenciaModelo.h"
#include <vector>
#include <string>

class Frase {
public:
	Frase(std::vector< std::string >* unaFraseACompletar);
	unsigned getModelo(unsigned numeroModelo, unsigned index);
	unsigned getTamanioFrase();
	std::string devolverContexto(int numeroModelo, int inicio);
	std::string devolverPalabra(unsigned index);
	void setFrecuencia(float penalizacion, unsigned long frecuencia, unsigned numeroModelo, unsigned index);
	void setModelo(unsigned numeroModelo, unsigned index);
	virtual ~Frase();

private:
	std::vector< std::string >* fraseACompletar;
	std::vector< FrecuenciaModelo* >* frecuencias;
	unsigned indiceDondeCompletar;
	void inicializarFrecuencias();
};

#endif /* FIUBA_DATOS_PREDICTOR_FRASE_H_ */
