/*
 * Frase.h
 *
 *  Created on: 30/11/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_PREDICTOR_FRASE_H_
#define FIUBA_DATOS_PREDICTOR_FRASE_H_

#include "../fiuba.datos.predictor/FrecuenciaModelo.h"
#include "../fiuba.datos.predictor/Completador.h"
#include "../fiuba.datos.ppmc/ModelosSuperiores.h"
#include "../fiuba.datos.ppmc/Modelo1.h"
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
	Completador* devolverFrecuenciaMinima(unsigned numeroFrase);
	void setPalabraConMayorFrecuencia(ModelosSuperiores* modelosSuperiores,std::string contexto, unsigned index, unsigned numeroModelo);
	void setPalabraConMayorFrecuencia(Modelo1* modelo1,std::string contexto, unsigned index, unsigned numeroModelo);
	void setPalabraConMayorFrecuencia(std::string palabraConMayorFrecuencia, unsigned index, unsigned numeroModelo);
	void borrarFrecuencias();
	std::vector< FrecuenciaModelo* >* getFrecuencias();
	virtual ~Frase();

private:
	std::vector< std::string >* fraseACompletar;
	std::vector< FrecuenciaModelo* >* frecuencias;
	unsigned indiceDondeCompletar;
	unsigned tamanioFrecuencias;
	void inicializarFrecuencias();
	std::string buscarPalabraConMayorFrecuencia(ModelosSuperiores *modelosSuperiores, std::string contexto);
	std::string buscarPalabraConMayorFrecuencia(Modelo1 *modelo1, std::string contexto);

};

#endif /* FIUBA_DATOS_PREDICTOR_FRASE_H_ */
