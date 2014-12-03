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
	Contexto* contexto = this->contextos->getContextos(claveContexto);
	return contexto->existePalabra(clavePalabra);
}

Jenkins* ModelosSuperiores::getJenkins(){
	return this->unHash;
}

int ModelosSuperiores::getNumeroModelo(){
	return this->numeroModelo;
}

pair<unsigned long, bool>* ModelosSuperiores::devolverFrecuencia(string nombreContexto, string nombrePalabra){

	pair<unsigned long, bool >* frecExisteContexto = new pair<unsigned long, bool>;
	frecExisteContexto->first = 0;
	frecExisteContexto->second = false;
	unsigned long claveContexto = this->hashearContexto(nombreContexto);
	bool existeContexto = this->existeContexto(claveContexto);

	frecExisteContexto->second = existeContexto;
	if (existeContexto) {
		unsigned long clavePalabra =
				this->hashearPalabra(claveContexto, nombrePalabra);
		bool existePalabraEnContexto =
				this->existePalabraEnContexto(claveContexto, clavePalabra);
		if (existePalabraEnContexto) {
			frecExisteContexto->first = this->contextos->getFrecuencia(claveContexto, clavePalabra);
		}
	}

	return frecExisteContexto;
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

string ModelosSuperiores::devolverPalabraConMayorFrecuencia(string contexto){
	unsigned long clave = this->unHash->hashearConMod(contexto);
	Contexto *unContexto = this->contextos->getContextos(clave);

	string palabraConMayorFrecuencia = unContexto->devolverPalabraConMayorFrecuencia();
	return palabraConMayorFrecuencia;
}
/*void ModelosSuperiores::mostrarModelo(unsigned modelo){

	map<unsigned long, Contexto*>* mapaHashCtx = this->contextos->getMapaHash();


	for ( map<unsigned long, Contexto*>::const_iterator iterContexto = mapaHashCtx->begin();
		iterContexto != mapaHashCtx->end(); ++iterContexto ){

			cout << iterContexto->first << '\t' << "MapaFrecuencia:";
	        map<unsigned long, Palabra* >* mapaHashFrecuencia = iterContexto->second->getMapaFrecuencia()->getHashFrecuencia();
	        for ( map<unsigned long, Palabra*>::const_iterator iter2 = mapaHashFrecuencia->begin();
	        	iter2 != mapaHashFrecuencia->end(); ++iter2 ){
	        		cout << iter2->first << '\t' << iter2->second->getPalabra() << '\t'  <<  iter2->second->getFrecuencia() << " ";
			}
            cout<< '\n';
	}
}*/
