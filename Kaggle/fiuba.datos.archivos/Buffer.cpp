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

//void Buffer::cargar(ifstream handle, int inicioProximaLectura){
//	if (handle.is_open()){
//		handle.seekg(inicioProximaLectura);
//		// read data as a block:
//		handle.read (this->buffer,this->tamanioBuffer);
//	}
//}

int Buffer::getTamanio(){
	return this->tamanioBuffer;
}
Buffer::~Buffer() {
	delete[] buffer;
}

