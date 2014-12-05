/*
 * Archivo.cpp
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#include "Archivo.h"

using namespace std;

Archivo::Archivo(){
	this->tamanioBuffer = 0;
	this->parser = new Parser();
};

Archivo::Archivo(string rutaArchivo, int tamanioBuffer) {
	this->handle.open(rutaArchivo.c_str(), ios::in);
	this->inicioProximaLectura = 0;
	this->tamanioBuffer = tamanioBuffer;
	this->buffer = new BufferParser(this->tamanioBuffer + 1);
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
	this->buffer->cargar(this->inicioProximaLectura, this->handle);
}

void Archivo::cargarInicioProximaLectura(){
	string texto(this->buffer->getBuffer());
    this->inicioProximaLectura = texto.find_last_of('\n');
    //this->buffer->rellenarBuffer(this->inicioProximaLectura);
}

vector<string>* Archivo::parsearBuffer(char valorParseo){
	return this->parser->devolverPalabras(this->buffer, valorParseo);
}

vector<Frase*>* Archivo::parsearTest(string rutaArchivo, char valorParseo){
	string textoTest = parser->ParsearArchivoTxt(rutaArchivo);
	return this->parser->devolverFrases(textoTest, valorParseo);
}


Archivo::~Archivo() {
	this->handle.close();
	delete[] this->buffer;
}

