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
	Jenkins* getJenkins();
	MapaFrecuencia* getMapaFrecuencia();
	void setMapaFrecuencia(unsigned long hash, Palabra* palabra);
	unsigned long hashear(std::string palabraActual);
	bool existePalabra(unsigned long clavePalabra);
	unsigned long getFrecuencia(unsigned long clavePalabra);
	std::string devolverPalabraConMayorFrecuencia();
	virtual ~Contexto();
};

#endif /* FIUBA_DATOS_PPMC_CONTEXTO_H_ */
