#include "Contexto.h"

using namespace std;

Contexto::Contexto(string unNombre){
	this->nombre = unNombre;
	this->palabras = new list<Palabra*>;
}
Contexto::Contexto(){

}

//SE USA UNA LISTA. NO HASHEAMOS. PODRIA CAMBIAR!!.
void Contexto::agregarPalabra(Palabra* unaPalabra){

	Palabra* palabraExistente = this->devolverPalabra(unaPalabra);
	if (palabraExistente != NULL){
		palabraExistente->incrementarFrecuencia();
	}
	else{
		this->palabras->push_back(unaPalabra);
	}
}

Palabra* Contexto::devolverPalabra(Palabra* unaPalabra){

	list<Palabra*>::iterator it = this->palabras->begin();
	Palabra* palabraExistente;
	bool palabraEncontrada = false;
	it = this->palabras->end();
	it++;
	while( (it != this->palabras->end()) || !(palabraEncontrada)){
		palabraExistente = (*it);
		palabraEncontrada = palabraExistente->esIgualA(unaPalabra);
		it++;
	}
	if (palabraEncontrada)
		return palabraExistente;
	else
		return NULL;
}

Palabra* Contexto::devolverPrimeraPalabra(){
	list<Palabra*>::iterator it = this->palabras->begin();
	return (*it);
}

bool Contexto::esIgualA(Contexto* unContexto){
	if(this->nombre == unContexto->getNombre())
		return true;
	return false;
}

string Contexto::getNombre(){
	return this->nombre;
}

Contexto::~Contexto() {
	delete this->palabras;
}
