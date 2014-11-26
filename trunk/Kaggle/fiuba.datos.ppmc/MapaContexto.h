/*
 * MapaContexto.h
 *
 *  Created on: 19/11/2014
 *      Author: hernan
 */

#ifndef FIUBA_DATOS_PPMC_MAPACONTEXTO_H_
#define FIUBA_DATOS_PPMC_MAPACONTEXTO_H_

#include <map>
#include "../fiuba.datos.ppmc/Contexto.h"
#include "../fiuba.datos.ppmc/MapaFrecuencia.h"

class MapaContexto {
public:
	MapaContexto();
	Contexto getContextos(unsigned long clave);
	void agregarContexto(unsigned long clave, std:: string nombrePalabra, int numeroModelo);
	void agregarContextoExistente(unsigned long clave, std:: string nombrePalabra);
	bool existeClave(unsigned long);
	std::map<unsigned long, Contexto*>* getMapaHash();
	unsigned long hashearPalabra(unsigned long claveContexto, std::string palabraActual);
	virtual ~MapaContexto();

private:
	std::map<unsigned long, Contexto*> *hashContexto;
	int devolverPrimo(int numeroModelo);
};

#endif /* FIUBA_DATOS_PPMC_MAPACONTEXTO_H_ */
