#ifndef FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_
#define FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_

#include <list>
#include "../fiuba.datos.ppmc/Contexto.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"

class ModelosSuperiores {
private:
	list<Contexto*>* contextos;
	int numeroDeModelo;
	HashingUniversalS* unHash;
	int hashearContexto(Contexto* unContexto);

public:
	ModelosSuperiores(int numeroDeModelo, int primo);
	void agregarContexto(Contexto* unContexto);

	~ModelosSuperiores();

};

#endif /* FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_ */
