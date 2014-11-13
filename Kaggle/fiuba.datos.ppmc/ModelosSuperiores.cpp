#include "ModelosSuperiores.h"

using namespace std;

//Cada Modelo va a tener un primo conveniente.
//Cuanto mas alto el Modelo, mas alto el primo.
ModelosSuperiores::ModelosSuperiores(int numeroDeModelo,int primo){
	this->contextos = new list<Contexto*>;
	this->numeroDeModelo = numeroDeModelo;

	this->unHash = new HashingUniversalS(primo);
}

ModelosSuperiores::~ModelosSuperiores() {
	delete this->contextos;
}
void ModelosSuperiores::agregarContexto(Contexto* unContexto){
	int indice = this->hashearContexto(unContexto);

	Palabra* unEscape = new Palabra("esc");
	unContexto->agregarPalabra(unEscape);

	list<Contexto*>::iterator it;
	it = this->contextos->begin();
   	advance(it,indice);
   	this->contextos->insert(it, unContexto);
}

int ModelosSuperiores::hashearContexto(Contexto* unContexto){

	return this->unHash->hashString(unContexto->getNombre());
}
