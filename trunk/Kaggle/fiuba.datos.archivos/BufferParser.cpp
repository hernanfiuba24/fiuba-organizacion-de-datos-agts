#include "BufferParser.h"

BufferParser::BufferParser(int tamanioBuffer) {
	this->tamanioBuffer = tamanioBuffer;
	this->buffer = new char[this->tamanioBuffer];
}

int BufferParser::getTamanio(){
	return this->tamanioBuffer;
}

char* BufferParser::getBuffer(){
	return this->buffer;
}

void BufferParser::cargar(int inicioProximaLectura, std::ifstream &archivoBuffer){
	if (archivoBuffer.is_open()){
		archivoBuffer.seekg(inicioProximaLectura);
		std::fill_n(buffer, this->tamanioBuffer + 1, '\0');
		archivoBuffer.read(this->buffer,this->tamanioBuffer);
	}
}

void BufferParser::rellenarBuffer(int inicioProximaLectura){
	int indexRelleno = inicioProximaLectura;
	for (int i = indexRelleno; i < this->tamanioBuffer; ++i) {
		std::fill_n(buffer, i , '\0');
	}
}

BufferParser::~BufferParser() {
	delete[] buffer;
}

