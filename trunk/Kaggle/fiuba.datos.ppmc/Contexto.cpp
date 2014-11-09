#include "Contexto.h"

Contexto::Contexto(){
	this->palabras = new list<Palabra>;
}

void Contexto::agregarPalabra(string unaPalabra){
	std::list<Palabra>::iterator it;
    it = this->palabras->begin();
    it++;
	this->palabras->insert(it, unaPalabra);
}

string Contexto::getNombre(){
	return this->nombre;
}

Contexto::~Contexto() {
	delete this->palabras;
}
