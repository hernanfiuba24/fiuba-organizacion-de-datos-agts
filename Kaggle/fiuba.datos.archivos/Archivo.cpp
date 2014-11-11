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
	this->buffer = new char[this->tamanioBuffer];
}

void Archivo::cargarBuffer(){
	this->cargar();
	this->inicioProximaLectura += this->tamanioBuffer;
	this->inicioProximaLectura += 1;
}

void Archivo::cargar(){
	if (this->handle.is_open()){
			this->handle.seekg(this->inicioProximaLectura);
			// read data as a block:
			this->handle.read (this->buffer,this->tamanioBuffer);
		}
}

list<char*>* Archivo::parsearBuffer(){
	Parser* unParser = new Parser();
	return unParser->devolverPalabras(this->buffer);
}

Archivo::~Archivo() {
	this->handle.close();
	delete[] this->buffer;
}

