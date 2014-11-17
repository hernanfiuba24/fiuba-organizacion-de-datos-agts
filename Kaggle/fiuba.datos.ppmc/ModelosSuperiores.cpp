#include "ModelosSuperiores.h"

using namespace std;

//Cada Modelo va a tener un primo conveniente.
//Cuanto mas alto el Modelo, mas alto el primo.
ModelosSuperiores::ModelosSuperiores(int numeroDeModelo, unsigned int tamanio){

	this->contextos = new Contexto[tamanio];
	this->numeroDeModelo = numeroDeModelo;
}

ModelosSuperiores::~ModelosSuperiores() {
	delete this->contextos;
}
void ModelosSuperiores::agregarContexto(Contexto* unContexto){
	int indice = this->hashearContexto(unContexto);

	Palabra* unEscape = new Palabra("esc");
	unContexto->agregarPalabra(unEscape);



}

int ModelosSuperiores::hashearContexto(Contexto* unContexto){
    string nombreContexto = unContexto->getNombre();
	return this->unHash->hashString(nombreContexto);
}
