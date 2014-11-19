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


class MapaFrecuencia {
public:
	MapaFrecuencia();
	unsigned getFrecuencia(unsigned clave);
	void incrementarFrecuencia(unsigned clave);
	//bool esIgualA(MapaFrecuencia* unaPalabra);

private:
	//size_t frecuencia;
	//std::string nombre;
	std::map<unsigned*, unsigned*> hashFrecuencia;
};

#endif /* FIUBA_DATOS_PPMC_MAPAFRECUENCIA_H_ */
