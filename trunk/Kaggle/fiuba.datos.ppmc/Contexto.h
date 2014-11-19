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
	Contexto(unsigned primo);
	Contexto();
	void agregarPalabra(std::string nombrePalabra);
	//Palabra* devolverPalabra(Palabra* unaPalabra);
	//Palabra* devolverPrimeraPalabra();
	bool esIgualA(Contexto* unContexto);
	std::string getNombre();
	virtual ~Contexto();
};

#endif /* FIUBA_DATOS_PPMC_CONTEXTO_H_ */
