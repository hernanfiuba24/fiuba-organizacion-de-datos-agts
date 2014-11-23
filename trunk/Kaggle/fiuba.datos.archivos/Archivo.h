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
#include <list>
#include "../fiuba.datos.archivos/Buffer.h"
#include "../fiuba.datos.archivos/Parser.h"


class Archivo {
public:
	Archivo(std::string rutaArchivo, int tamanioBuffer);
	void cargarBuffer();
	//metodo de prueba, se puede borrar
	void mostrarBuffer();
	std::list<std::string>* parsearBuffer(char valorParseo);
	std::list<std::string>* parsearTest(std::string rutaArchivo, char valorParseo);
	int cargarInicioProximaLectura();
	virtual ~Archivo();
private:
	int tamanioBuffer;
	std::ifstream handle;
    int inicioProximaLectura;
    Parser* parser;
    Buffer* buffer;
    void cargar();
};

#endif /* FIUBA_DATOS_ARCHIVOS_ARCHIVO_H_ */
