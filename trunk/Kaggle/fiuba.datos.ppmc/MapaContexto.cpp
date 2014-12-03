/*
 * MapaContexto.cpp
 *
 *  Created on: 19/11/2014
 *      Author: hernan
 */

#include "MapaContexto.h"

using namespace std;

MapaContexto::MapaContexto() {
	this->hashContexto = new map<unsigned long, Contexto*>;
}

map<unsigned long, Contexto*>* MapaContexto::getMapaHash(){
	return this->hashContexto;
}
void MapaContexto::agregarContexto(unsigned long clave, string nombrePalabra, int numeroModelo){
    int primo = this->devolverPrimo(numeroModelo);
    Contexto* unContexto = new Contexto(primo);
    unContexto->agregarPalabra(nombrePalabra);

    pair<unsigned, Contexto*> hashContexto = make_pair(clave, unContexto);

	this->hashContexto->insert(hashContexto);
}

void MapaContexto::agregarContextoExistente(unsigned long clave, string nombrePalabra){
	Contexto* contextoExistente = (*this->hashContexto)[clave];
	contextoExistente->agregarPalabra(nombrePalabra);

}
//CAMBIAR PRIMOS??????????? PELA
int MapaContexto::devolverPrimo(int numeroModelo){
	int primo;
	if(numeroModelo == 1)
		primo = 50001;
	else if (numeroModelo == 2)
		primo= 40001;
	else if (numeroModelo == 3)
		primo= 30001;
	else if (numeroModelo == 4)
		primo= 30001;

	return primo;
}

Contexto* MapaContexto::getContextos(unsigned long clave){
	map<unsigned long, Contexto*>::iterator iter = this->hashContexto->find(clave);
	Contexto* unContexto = (*iter).second;
	return (unContexto);
	//return (*(*this->hashContexto)[clave]);
}

bool MapaContexto::existeClave(unsigned long clave){

    return (this->hashContexto->find(clave) != this->hashContexto->end());

}

unsigned long MapaContexto::hashearPalabra(unsigned long claveContexto, string palabraActual){

	Contexto* unContexto = (*this->hashContexto)[claveContexto];
	return unContexto->hashear(palabraActual);
}

unsigned long MapaContexto::getFrecuencia(unsigned long claveContexto, unsigned long clavePalabra){

//	map<unsigned long, Contexto*>::iterator iter = this->hashContexto->find(claveContexto);
//	Contexto* unContexto = (*iter).second;
//	unsigned long frecuencia = unContexto->getFrecuencia(clavePalabra);
//	return frecuencia;

//	MapaFrecuencia* mapa = unContexto->getMapaFrecuencia();
//	map<unsigned long, Palabra*> * mapaFrec = mapa->getHashFrecuencia();

//	map<unsigned long, Palabra*>::iterator iter2 = mapaFrec->find(clavePalabra);

//	unsigned long fre = (*iter2).second->getFrecuencia();

	Contexto* contexto = (*this->hashContexto)[claveContexto];
	unsigned long frecuencia = contexto->getFrecuencia(clavePalabra);
	return frecuencia;
}

MapaContexto::~MapaContexto(){
	for(map<unsigned long, Contexto*>::iterator itr = this->hashContexto->begin(); itr != this->hashContexto->end(); itr++)
		delete itr->second;
	delete this->hashContexto;
}

