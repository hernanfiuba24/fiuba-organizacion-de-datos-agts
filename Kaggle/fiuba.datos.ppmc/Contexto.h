/*
 * Contexto.h
 *
 *  Created on: 19/10/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_PPMC_CONTEXTO_H_
#define FIUBA_DATOS_PPMC_CONTEXTO_H_

#include <string>
#include "../fiuba.datos.ppmc/MapaFrecuencia.h"
#include "../fiuba.datos.hashing/Jenkins.h"

class Contexto {
private:
	//std::string nombre;
	//std::vector<Palabra*>* palabras;
	MapaFrecuencia *unMapa;
	Jenkins *unHash;

public:
	Contexto(unsigned long primo);
	void agregarPalabra(std::string nombrePalabra);
	bool esIgualA(Contexto* unContexto);
	std::string getNombre();
	MapaFrecuencia* getMapaFrecuencia();
	virtual ~Contexto();
};

#endif /* FIUBA_DATOS_PPMC_CONTEXTO_H_ */
