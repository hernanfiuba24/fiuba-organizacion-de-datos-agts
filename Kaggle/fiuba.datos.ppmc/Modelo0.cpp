/*
 * Modelo0.cpp
 *
 *  Created on: 9/11/2014
 *      Author: ezequiel
 */

#include "Modelo0.h"

using namespace std;

Modelo0::Modelo0(unsigned primo){
	this->unHash = new Jenkins(primo);
	this->unMapa = new MapaFrecuencia();
	//this->palabras = new vector<Palabra*>;
}

void Modelo0::agregarPalabra(string unNombre){

	unsigned clave = this->unHash->hashearConMod(unNombre);

	if (this->unMapa->existeClave(clave))
		this->unMapa->incrementarFrecuencia(clave);
	else
		this->unMapa->agregarClave(clave);

}
	/*
	Palabra* palabraExistente = this->devolverPalabra(unaPalabra);
		if (palabraExistente != NULL){
			palabraExistente->incrementarFrecuencia();
		}
		else{
			this->palabras->push_back(unaPalabra);
		}

*/

/*Palabra* Modelo0::devolverPalabra(Palabra* unaPalabra){

vector<Palabra*>::iterator it = this->palabras->begin();
	Palabra* palabraExistente;
	bool palabraEncontrada = false;
	while( (it != this->palabras->end()) || !(palabraEncontrada)){
		palabraExistente = (*it);
		palabraEncontrada = palabraExistente->esIgualA(unaPalabra);
	}
	if (palabraEncontrada)
		return palabraExistente;
	else
		return NULL;
}*/

Modelo0::~Modelo0() {
	//CONTROLAR ESTE DESTRUCTOR!!!!
//	for (list<Palabra*>::iterator it = this->palabras->begin(); it <= this->palabras->end();it++){
//		delete (*it);
//	}
	delete this->unMapa;
}

