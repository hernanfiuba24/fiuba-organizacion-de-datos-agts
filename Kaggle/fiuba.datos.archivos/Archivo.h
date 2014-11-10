/*
 * Archivo.h
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_ARCHIVOS_ARCHIVO_H_
#define FIUBA_DATOS_ARCHIVOS_ARCHIVO_H_

#include <fstream>
#include <string>
#include "../fiuba.datos.archivos/Buffer.h"


class Archivo {
public:
	Archivo(std::string rutaArchivo, int tamanioBuffer);
	void cargarBuffer();
	virtual ~Archivo();
private:
	char* buffer;
	int tamanioBuffer;
	std::ifstream handle;
    int inicioProximaLectura;
    void cargar();
};

#endif /* FIUBA_DATOS_ARCHIVOS_ARCHIVO_H_ */
