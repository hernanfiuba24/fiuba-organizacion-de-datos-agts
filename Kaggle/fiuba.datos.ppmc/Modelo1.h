/*
 * Modelo1.h
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */


#ifndef MODELO1_H_
#define MODELO1_H_

//#include <vector>
#include "Contexto.h"
#include "../fiuba.datos.hashing/Jenkins.h"
#include "../fiuba.datos.ppmc/MapaContexto.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"

class Modelo1 {
public:
	Modelo1(unsigned long primo, int numeroModelo);
	std::pair<unsigned long, bool>* devolverFrecuencia(std::string nombreContexto, std::string nombrePalabra);
	void agregarContexto(std::string nombreContexto, std::string nombrePalabra);
	unsigned long hashearContexto(std::string contextoAHashear);
	bool existeContexto(unsigned long claveContexto);
	unsigned long hashearPalabra(unsigned long claveContexto, std::string palabraActual);
	bool existePalabraEnContexto(unsigned long claveContexto, unsigned long clavePalabra);
	std::string devolverPalabraConMayorFrecuencia(std::string contexto);
	MapaContexto* getMapa();
	float devolverPenalizacion();
	Jenkins* getJenkins();
	virtual ~Modelo1();

private:
	//std::vector<Contexto*>* contextos;
	MapaContexto *contextos;
	Jenkins *unHash;
	int numeroModelo;

};

#endif /* MODELO1_H_ */
