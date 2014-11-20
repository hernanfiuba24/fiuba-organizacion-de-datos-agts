#ifndef FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_
#define FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_

#include <map>
#include "../fiuba.datos.ppmc/MapaContexto.h"
#include "../fiuba.datos.hashing/Jenkins.h"

class ModelosSuperiores {
public:

	ModelosSuperiores(unsigned long primo, int numeroModelo);
	void agregarContexto(std::string nombreContexto, std::string nombrePalabra);
	//Contexto* devolverContexto(Contexto* unContexto);
	virtual ~ModelosSuperiores();

private:
	MapaContexto *contextos;
	Jenkins *unHash;
	int numeroModelo;
/*private:
	Contexto *contextos;
	int numeroDeModelo;
	unsigned long tamanioTablaDeHash;
	bool existeContexto(Contexto* unContexto, uint32_t indice);
	bool existeContexto(Contexto* unContexto, uint64_t indice);

public:
	ModelosSuperiores(int numeroDeModelo, unsigned int tamanio);
	void agregarContexto(Contexto* unContexto);

	~ModelosSuperiores();
*/
};

#endif /* FIUBA_DATOS_PPMC_MODELOSSUPERIORES_H_ */
