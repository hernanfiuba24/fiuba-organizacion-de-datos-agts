/*
 * Contexto.h
 *
 *  Created on: 19/10/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_PPMC_CONTEXTO_H_
#define FIUBA_DATOS_PPMC_CONTEXTO_H_

#include <string>
#include <map>

using namespace std;

typedef pair<string, int> palabraFrecuencia;

class Contexto {
private:
	string contexto;
	map<string,int> palabrasFrecuencias;

public:
	Contexto();
	Contexto(int numeroModelo);
	void agregarPalabra(string unaPalabra);
	virtual ~Contexto();
};

#endif /* FIUBA_DATOS_PPMC_CONTEXTO_H_ */
