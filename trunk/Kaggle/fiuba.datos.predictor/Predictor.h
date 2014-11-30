/*
 * Predictor.h
 *
 *  Created on: 30/11/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_PREDICTOR_PREDICTOR_H_
#define FIUBA_DATOS_PREDICTOR_PREDICTOR_H_

#include "../fiuba.datos.predictor/FrecuenciaModelo.h"
#include "../fiuba.datos.predictor/Frase.h"
#include "../fiuba.datos.ppmc/ModelosSuperiores.h"
#include "../fiuba.datos.ppmc/Modelo1.h"
#include "../fiuba.datos.ppmc/Modelo0.h"
#include "../fiuba.datos.archivos/SerializadorXml.h"
#include <vector>
#include <string>

class Predictor {
public:
	Predictor();
	void completarFrases(std::vector<Frase*>* frasesACompletar, Modelo1* modelo1, Modelo0* modelo0);
	void predecirUnaFrase(Frase* fraseACompletar, ModelosSuperiores* modelosSuperiores);
	void predecirUnaFrase(Frase* fraseACompletar, Modelo1* modelo1);
	void predecirUnaFrase(Frase* fraseACompletar, Modelo0* modelo0);
	ModelosSuperiores* cargarModelosSuperiores(unsigned numeroModelo);
	virtual ~Predictor();

private:
	void inicializarFrecuencias(std::vector< FrecuenciaModelo* >* frecuencias);
	std::string devolverContexto(Frase* fraseACompletar, unsigned numeroModelo, unsigned inicio);
	std::string devolverPalabra(Frase* fraseACompletar, unsigned numeroModelo, unsigned index);
};

#endif /* FIUBA_DATOS_PREDICTOR_PREDICTOR_H_ */
