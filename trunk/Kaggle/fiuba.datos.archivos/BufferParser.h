#include <string>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>

#ifndef Included_BufferParser_H
#define Included_BufferParser_H

class BufferParser {
public:
	BufferParser(int tamanioBuffer);
	int getTamanio();
	char* getBuffer();
	void rellenarBuffer(int inicioProdicmaLectura);
	void cargar(int inicioProximaLectura, std::ifstream &archivoBuffer);
	virtual ~BufferParser();

private:
	char* buffer;
	int tamanioBuffer;
};

#endif // Included_BufferParser_H
