/*
 * Archivo.h
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_ARCHIVOS_BUFFER_H_
#define FIUBA_DATOS_ARCHIVOS_BUFFER_H_

#include <fstream>

class Buffer {
public:
	Buffer(int tamanioBuffer);
	//void cargar(std::ifstream handle, int inicioProximaLectura);
	int getTamanio();
	virtual ~Buffer();

private:
	char* buffer;
	int tamanioBuffer;
};

#endif /* FIUBA_DATOS_ARCHIVOS_BUFFER_H_ */
