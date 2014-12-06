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
#include "../fiuba.datos.ppmc/PPMC.h"
#include <iostream>

namespace std {

class Predictor {
public:
	Predictor();
	void completarFrases(vector<Frase*>* frasesACompletar, Modelo1* modelo1, Modelo0* modelo0, PPMC *unPPMC);
	void predecirUnaFrase(Frase* fraseACompletar, ModelosSuperiores* modelosSuperiores);
	void predecirUnaFrase(Frase* fraseACompletar, Modelo1* modelo1);
	void predecirUnaFrase(Frase* fraseACompletar, Modelo0* modelo0, std::string palabraConMayorFrecuencia);
	ModelosSuperiores* cargarModelosSuperiores(unsigned numeroModelo);
	ModelosSuperiores* ProvisoriaCargarModelosSuperiores(unsigned numeroModelo,PPMC *unPPMC);
	virtual ~Predictor();
	void mostrarFrecuencias(vector<Frase*>* frasesACompletar);
	void mostrarFrases(vector<Frase*>* frasesACompletar);

private:
	void inicializarFrecuencias(vector< FrecuenciaModelo* >* frecuencias);
	std::string devolverContexto(Frase* fraseACompletar, unsigned numeroModelo, unsigned inicio);
	std::string devolverPalabra(Frase* fraseACompletar, unsigned numeroModelo, unsigned index);
	void completarFrecuencias(vector<Frase* >* frasesACompletar, Modelo1* modelo1, Modelo0* modelo0, PPMC *unPPMC);
	Completador* hallarLaFrecuenciaMinima(Frase* fraseACompletar, unsigned numeroFrase);
	void cargarCompletadores(vector<Frase*>* frasesACompletar);
	void setearCompletadorModelo(Completador* unCompletador);
	void completarPalabrasEnFrases(vector<Frase* >* frasesACompletar);
	void completarPalabrasDeLosCompletadores(vector<Frase* >* frasesACompletar);
	void borrarFrecuencias(std::vector<Frase*>* frasesACompletar);

	vector<Completador*>* completadores;

};

}

#endif /* FIUBA_DATOS_PREDICTOR_PREDICTOR_H_ */
