/*
 * Archivo.cpp
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#include "Archivo.h"

using namespace std;

Archivo::Archivo(string rutaArchivo, int tamanioBuffer) {
	this->handle.open(rutaArchivo.c_str(), ios::in);
	this->inicioProximaLectura = 0;
	this->tamanioBuffer = tamanioBuffer;
	this->buffer = new char[this->tamanioBuffer + 1];
}

void Archivo::mostrarBuffer(){
	cout<<this->buffer;
}

void Archivo::cargarBuffer(){
	this->cargar();
	this->inicioProximaLectura += this->tamanioBuffer;
	this->inicioProximaLectura += 1;
}

void Archivo::cargar(){
	if (this->handle.is_open()){
			this->handle.seekg(this->inicioProximaLectura);
			fill_n(buffer, this->tamanioBuffer + 1, '\0');
			// read data as a block:
			this->handle.read (this->buffer,this->tamanioBuffer + 1);
		}
}

list<string>* Archivo::parsearBuffer(char valorParseo){
	Parser* unParser = new Parser();
	return unParser->devolverPalabras(this->buffer, valorParseo);

}

Archivo::~Archivo() {
	this->handle.close();
	delete[] this->buffer;
}

