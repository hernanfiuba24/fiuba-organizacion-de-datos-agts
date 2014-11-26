#include "Contexto.h"

using namespace std;

Contexto::Contexto(unsigned long primo){
	this->unMapa = new MapaFrecuencia();
	this->unHash = new Jenkins(primo);
}

MapaFrecuencia* Contexto::getMapaFrecuencia(){
	return this->unMapa;
}

//SE USA UNA LISTA. NO HASHEAMOS. PODRIA CAMBIAR!!.
void Contexto::agregarPalabra(string nombrePalabra){

	unsigned long clave = this->unHash->hashearConMod(nombrePalabra);
	if (this->unMapa->existeClave(clave))
			this->unMapa->incrementarFrecuencia(clave);
		else
			this->unMapa->agregarClave(clave, nombrePalabra);
}

unsigned long Contexto::hashear(string palabraActual){
	return this->unHash->hashearConMod(palabraActual);
}

Contexto::~Contexto() {
	delete this->unHash;
	delete this->unMapa;
}
