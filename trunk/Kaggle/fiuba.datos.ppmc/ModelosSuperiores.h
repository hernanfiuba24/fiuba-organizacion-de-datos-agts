#ifndef FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_
#define FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_

#include <list>
#include "../fiuba.datos.ppmc/Contexto.h"
#include "../fiuba.datos.hashing/Jenkins.h"

class ModelosSuperiores {
private:
	Contexto *contextos;
	int numeroDeModelo;
	unsigned long tamanioTablaDeHash;
	bool existeContexto(Contexto* unContexto, uint32_t indice);
	bool existeContexto(Contexto* unContexto, uint64_t indice);

public:
	ModelosSuperiores(int numeroDeModelo, unsigned int tamanio);
	void agregarContexto(Contexto* unContexto);

	~ModelosSuperiores();

};

#endif /* FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_ */
