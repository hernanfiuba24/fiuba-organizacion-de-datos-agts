#include "ModelosSuperiores.h"

using namespace std;

ModelosSuperiores::ModelosSuperiores(unsigned long primo, int numeroDeModelo){
	this->unHash = new Jenkins(primo);
	this->contextos = new MapaContexto();
	this->numeroModelo = numeroDeModelo;
}

MapaContexto* ModelosSuperiores::getMapa(){
	return this->contextos;
}

ModelosSuperiores::~ModelosSuperiores() {
	delete this->contextos;
	delete this->unHash;
}

void ModelosSuperiores::agregarContexto(string nombreContexto, string nombrePalabra){

	unsigned clave = this->unHash->hashearConMod(nombreContexto);
	bool existeClave = this->contextos->existeClave(clave);
	if (existeClave)
		this->contextos->agregarContextoExistente(clave, nombrePalabra);
	else
		this->contextos->agregarContexto(clave, nombrePalabra, this->numeroModelo);

}

unsigned long ModelosSuperiores::hashearContexto(string contextoAHashear){

	return this->unHash->hashearConMod(contextoAHashear);
}

unsigned long ModelosSuperiores::hashearPalabra(unsigned long claveContexto, string palabraActual){
	return this->contextos->hashearPalabra(claveContexto, palabraActual);
}

bool ModelosSuperiores::existeContexto(unsigned long claveContexto){

	return this->contextos->existeClave(claveContexto);
}

bool ModelosSuperiores::existePalabraEnContexto(unsigned long claveContexto, unsigned long clavePalabra){
	Contexto contexto = this->contextos->getContextos(claveContexto);
	return contexto.existePalabra(clavePalabra);
}

unsigned ModelosSuperiores::devolverFrecuencia(string nombreContexto, string nombrePalabra){

	unsigned frecuencia = 0;
	unsigned long claveContexto = this->hashearContexto(nombreContexto);

	bool existeContexto = this->existeContexto(claveContexto);

	if (existeContexto) {
		unsigned long clavePalabra =
				this->hashearPalabra(claveContexto, nombrePalabra);
		bool existePalabraEnContexto =
				this->existePalabraEnContexto(claveContexto, clavePalabra);
		if (existePalabraEnContexto) {
			frecuencia =  this->contextos->getFrecuencia(claveContexto, clavePalabra);
		}
	}
	return frecuencia;
}

float ModelosSuperiores::devolverPenalizacion(unsigned numeroModelo){
	float penalizacion;
	if (numeroModelo == 2)
	    penalizacion = 0.16;
	else if (numeroModelo == 3)
		penalizacion = 0.4;
	else
		penalizacion = 1;
    return penalizacion;
}
