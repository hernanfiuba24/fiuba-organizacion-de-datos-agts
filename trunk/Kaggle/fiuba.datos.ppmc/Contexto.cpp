#include "Contexto.h"

using namespace std;

Contexto::Contexto(string unNombre, int primo){
	this->nombre = unNombre;
	this->palabras = new list<Palabra*>;
	this->unHash = new HashingUniversalS(primo);
}

void Contexto::agregarPalabra(Palabra* unaPalabra){
	int indice = this->hashearPalabra(unaPalabra);

	std::list<Palabra*>::iterator it;
    it = this->palabras->begin();
    advance(it,indice);
	this->palabras->insert(it, unaPalabra);
}

string Contexto::getNombre(){
	return this->nombre;
}
int Contexto::hashearPalabra(Palabra* unaPalabra){
	return (this->unHash->hashString(unaPalabra->getNombre()));
}

Contexto::~Contexto() {
	delete this->palabras;
}
