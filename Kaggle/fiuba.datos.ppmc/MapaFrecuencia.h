/*
 * Palabra.h
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#ifndef FIUBA_DATOS_PPMC_MAPAFRECUENCIA_H_
#define FIUBA_DATOS_PPMC_MAPAFRECUENCIA_H_
#include <string>
#include <map>
#include "../fiuba.datos.ppmc/Palabra.h"


class MapaFrecuencia {
public:
	MapaFrecuencia();
	unsigned long getFrecuencia(unsigned long clave);
	void setFrecuencia(unsigned long clave, unsigned long frecuencia);
	std::map<unsigned long, Palabra* >* getHashFrecuencia();
	void incrementarFrecuencia(unsigned long clave);
	bool existeClave(unsigned long clave);
	void agregarClave(unsigned long clave, std::string palabraAgregar);
	void agregarClave(unsigned long hashPalabra, Palabra* palabraAgregar);
	//bool esIgualA(MapaFrecuencia* unaPalabra);

private:
	//size_t frecuencia;
	//std::string nombre;
	std::map<unsigned long, Palabra*> *hashFrecuencia;
};

#endif /* FIUBA_DATOS_PPMC_MAPAFRECUENCIA_H_ */
