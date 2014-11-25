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
	unsigned getFrecuencia(unsigned long clave);
	std::map<unsigned long, std::pair<std::string, unsigned> >* getHashFrecuencia();
	void incrementarFrecuencia(unsigned long clave);
	bool existeClave(unsigned long clave);
	void agregarClave(unsigned long clave, std::string palabraAgregar);
	//bool esIgualA(MapaFrecuencia* unaPalabra);

private:
	//size_t frecuencia;
	//std::string nombre;
	std::map<unsigned long, std::pair<std::string, unsigned> >* hashFrecuencia;
};

#endif /* FIUBA_DATOS_PPMC_MAPAFRECUENCIA_H_ */
