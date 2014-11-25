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

	/*Palabra* palabraExistente = this->devolverPalabra(unaPalabra);
	if (palabraExistente != NULL){
		palabraExistente->incrementarFrecuencia();
	}
	else{
		this->palabras->push_back(unaPalabra);
	}
	*/
	unsigned long clave = this->unHash->hashearConMod(nombrePalabra);
	if (this->unMapa->existeClave(clave))
			this->unMapa->incrementarFrecuencia(clave);
		else
			this->unMapa->agregarClave(clave, nombrePalabra);
}
/*
 Contexto::devolverPalabra(Palabra* unaPalabra){

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
*/

Contexto::~Contexto() {
	delete this->unHash;
	delete this->unMapa;
}
