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
