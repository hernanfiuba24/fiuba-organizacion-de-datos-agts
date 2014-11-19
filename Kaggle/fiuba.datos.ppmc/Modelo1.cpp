/*
 * Modelo1.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo1.h"

using namespace std;

Modelo1::Modelo1(unsigned primo){
	//this->contextos = new vector<Contexto*>;
	//CAMBIAR ESTE VALOR POR UN PRIMO AJUSTABLE AL MODELO
	this->unHash = new Jenkins(primo);
	this->contextos = new MapaContexto();

}

//CORREGIDO!!!
void Modelo1::agregarContexto(string nombreContexto, string nombrePalabra, int numeroModelo){
    /*
	Contexto* contextoExistente = this->devolverContexto(unContexto);
		if (contextoExistente != NULL){
			contextoExistente->agregarPalabra(unContexto->devolverPrimeraPalabra());
		}
		else{
			Palabra* unEscape = new Palabra("esc");
			unContexto->agregarPalabra(unEscape);
			this->contextos->push_back(unContexto);
		}
	*/
	unsigned clave = this->unHash->hashearConMod(nombreContexto);
	bool existeClave = this->contextos->existeClave(clave);
	if (existeClave)
		this->contextos->agregarContextoExistente(clave, nombrePalabra);
	else
		this->contextos->agregarContexto(clave, nombrePalabra, numeroModelo);

}
/*
Contexto* Modelo1::devolverContexto(Contexto* unContexto){

	vector<Contexto*>::iterator it = this->contextos->begin();
	Contexto* contextoExistente;
	bool contextoEncontrado = false;
	while( (it != this->contextos->end()) || !(contextoEncontrado)){
		contextoExistente = (*it);
		contextoEncontrado = contextoExistente->esIgualA(unContexto);
	}
	if (contextoEncontrado)
		return contextoExistente;
	else
		return NULL;
	//
	unsigned clave = this->unHash->hashearConMod(unContexto->getNombre());
	if (this->contextos(clave) == this->contextos.end())
	    return NULL;
	else
	    return this->contextos[clave];
	}


}
*/
Modelo1::~Modelo1() {
	//CONTROLAR ESTE DESTRUCTOR!!!!
//	for (list<Palabra*>::iterator it = this->contextos->begin(); it <= this->contextos->end();it++){
//		delete (*it);
//	}
	delete this->contextos;
	delete this->unHash;
}

