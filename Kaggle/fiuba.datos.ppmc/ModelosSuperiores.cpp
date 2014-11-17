#include "ModelosSuperiores.h"

using namespace std;

ModelosSuperiores::ModelosSuperiores(int numeroDeModelo, unsigned int tamanio){
	this->contextos = new Contexto[tamanio];
	this->numeroDeModelo = numeroDeModelo;
	this->tamanioTablaDeHash = tamanio;
}

ModelosSuperiores::~ModelosSuperiores() {
	delete[] this->contextos;
}
void ModelosSuperiores::agregarContexto(Contexto* unContexto){
	Jenkins *unHash = new Jenkins();
	uint32_t indice = unHash->hashearCon32Bits(unContexto->getNombre());
    if(this->existeContexto(unContexto, indice)){
    	this->contextos[indice].agregarPalabra(unContexto->devolverPrimeraPalabra());
 	}
    else{
    	Palabra* unEscape = new Palabra("esc");
    	unContexto->agregarPalabra(unEscape);
    	this->contextos[indice] = *unContexto;
    }
}

bool ModelosSuperiores::existeContexto(Contexto* unContexto, uint32_t indice){
	if (this->contextos[indice].getNombre() == unContexto->getNombre())
		return true;
	return false;
}

bool ModelosSuperiores::existeContexto(Contexto* unContexto, uint64_t indice){
	if (this->contextos[indice].getNombre() == unContexto->getNombre())
		return true;
	return false;
}
