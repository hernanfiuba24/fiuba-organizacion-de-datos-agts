#ifndef FIUBA_DATOS_PPMC_MODELO_H_
#define FIUBA_DATOS_PPMC_MODELO_H_

#include <list>

#include "../fiuba.datos.ppmc/Contexto.h"

class Modelo {
private:
	list<Contexto*>* contextos;
	int numeroDeModelo;
	int hashearContexto(Contexto* unContexto);

public:
	Modelo(int numeroDeModelo);
	void agregarContexto(Contexto* unContexto);

	~Modelo();

};

#endif /* FIUBA_DATOS_PPMC_MODELO_H_ */
