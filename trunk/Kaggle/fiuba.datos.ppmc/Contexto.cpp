#include "Contexto.h"

using namespace std;

Contexto::Contexto(unsigned long primo){
	this->unMapa = new MapaFrecuencia();
	this->unHash = new Jenkins(primo);
}

MapaFrecuencia* Contexto::getMapaFrecuencia(){
	return this->unMapa;
}

void Contexto::setMapaFrecuencia(unsigned long hash, Palabra* palabra){
	this->unMapa->agregarClave(hash, palabra->getPalabra());
	this->unMapa->setFrecuencia(hash, palabra->getFrecuencia());
}

void Contexto::agregarPalabra(string nombrePalabra){

	unsigned long clave = this->unHash->hashearConMod(nombrePalabra);
	if (this->unMapa->existeClave(clave))
			this->unMapa->incrementarFrecuencia(clave);
		else
			this->unMapa->agregarClave(clave, nombrePalabra);
}

Jenkins* Contexto::getJenkins(){
	return this->unHash;
}

unsigned long Contexto::hashear(string palabraActual){
	return this->unHash->hashearConMod(palabraActual);
}

bool Contexto::existePalabra(unsigned long clavePalabra){
	return this->unMapa->existeClave(clavePalabra);
}

unsigned long Contexto::getFrecuencia(unsigned long clavePalabra){
	unsigned long frec = this->unMapa->getFrecuencia(clavePalabra);
	return frec;
}
string Contexto::devolverPalabraConMayorFrecuencia(){
	string palabraConMayorFrecuencia = this->unMapa->devolverPalabraConMayorFrecuencia();
	return palabraConMayorFrecuencia;
}

Contexto::~Contexto() {
	delete this->unHash;
	delete this->unMapa;
}
