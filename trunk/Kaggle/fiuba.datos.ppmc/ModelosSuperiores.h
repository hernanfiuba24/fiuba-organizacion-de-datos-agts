#ifndef FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_
#define FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_

#include <map>
#include "../fiuba.datos.ppmc/MapaContexto.h"
#include "../fiuba.datos.hashing/Jenkins.h"

class ModelosSuperiores {
public:
	ModelosSuperiores(unsigned long primo, int numeroModelo);
	void agregarContexto(std::string nombreContexto, std::string nombrePalabra);
	MapaContexto *getMapa();
	void setMapaContexto(unsigned long hash, Contexto* contexto);
	std::pair<unsigned long, bool>* devolverFrecuencia(std::string nombreContexto, std::string nombrePalabra);
	float devolverPenalizacion(unsigned numeroModelo);
	Jenkins* getJenkins();
	int getNumeroModelo();
	std::string devolverPalabraConMayorFrecuencia(std::string contexto);
	virtual ~ModelosSuperiores();
//	void mostrarModelo(unsigned numeroModelo);

private:
	MapaContexto *contextos;
	Jenkins *unHash;
	int numeroModelo;

	unsigned long hashearContexto(std::string contextoAHashear);
	bool existeContexto(unsigned long claveContexto);

	unsigned long hashearPalabra(unsigned long claveContexto, std::string palabraActual);
	bool existePalabraEnContexto(unsigned long claveContexto, unsigned long clavePalabra);
};

#endif /* FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_ */
