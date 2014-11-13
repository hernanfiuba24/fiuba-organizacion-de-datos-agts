#include "Contexto.h"

using namespace std;

Contexto::Contexto(string unNombre){
	this->nombre = unNombre;
	this->palabras = new list<Palabra*>;
}

void Contexto::agregarPalabra(Palabra* unaPalabra){
	std::list<Palabra*>::iterator it;
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
