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
	this->buffer = new Buffer(this->tamanioBuffer + 1);
	this->parser = new Parser();
}

void Archivo::mostrarBuffer(){
	cout<<this->buffer;
}

void Archivo::cargarBuffer(){
	this->cargar();
	this->cargarInicioProximaLectura();
}

void Archivo::cargar(){
	this->buffer->cargar(this->handle, this->inicioProximaLectura);
}

int Archivo::cargarInicioProximaLectura(){
	string texto(this->buffer->getBuffer());
    this->inicioProximaLectura = texto.find_last_of('\n');
    this->buffer->rellenarBuffer(this->inicioProximaLectura);
}

list<string>* Archivo::parsearBuffer(char valorParseo){
	return this->parser->devolverPalabras(this->buffer, valorParseo);
}

list<string>* Archivo::parsearTest(string rutaArchivo, char valorParseo){
	ifstream archivoTest(rutaArchivo.c_str(), ios::in);
	char c = archivoTest.get();
    string textoTest = "";
	while (archivoTest.good()) {
	    textoTest += c;
		c = archivoTest.get();
	}

	return this->parser->devolverFrases(textoTest, valorParseo);
}

Archivo::~Archivo() {
	this->handle.close();
	delete[] this->buffer;
}

