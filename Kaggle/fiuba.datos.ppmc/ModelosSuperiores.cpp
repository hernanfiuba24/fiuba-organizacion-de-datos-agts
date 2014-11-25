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

	/*Jenkins *unHash = new Jenkins();
	uint32_t indice = unHash->hashearCon32Bits(unContexto->getNombre());
    if(this->existeContexto(unContexto, indice)){
    	this->contextos[indice].agregarPalabra(unContexto->devolverPrimeraPalabra());
 	}
    else{
    	Palabra* unEscape = new Palabra("esc");
    	unContexto->agregarPalabra(unEscape);
    	this->contextos[indice] = *unContexto;
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
*/
