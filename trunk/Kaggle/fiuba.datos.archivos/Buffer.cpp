/*
 * Archivo.cpp
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#include "Buffer.h"

using namespace std;

Buffer::Buffer(int tamanioBuffer) {
	this->tamanioBuffer = tamanioBuffer;
	this->buffer = new char[this->tamanioBuffer];
}

void Buffer::cargar(ifstream handle, int inicioProximaLectura){
	if (handle.is_open()){
		handle.seekg(inicioProximaLectura);
		fill_n(buffer, this->tamanioBuffer + 1, '\0');
		handle.read(this->buffer,this->tamanioBuffer);
	}
}

int Buffer::getTamanio(){
	return this->tamanioBuffer;
}


void Buffer::rellenarBuffer(int inicioProdicmaLectura){
	int tamanio = this->getTamanio();
	fill_n(buffer[inicioProdicmaLectura], (this->tamanioBuffer + 1) - inicioProdicmaLectura, '\0');
}


char* Buffer::getBuffer(){
	return this->buffer;
}

Buffer::~Buffer() {
	delete[] buffer;
}

