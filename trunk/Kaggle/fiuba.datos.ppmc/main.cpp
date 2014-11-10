/*
 * main.cpp
 *
 *  Created on: 21/10/2014
 *      Author: Alumnos
 */

#include "PPMC.h"
#include <iostream>
#include "../fiuba.datos.archivos/Archivo.h"

int main(){
	Archivo* unArchivo = new Archivo("/home/ezequiel/workspace/archivoPrueba.txt", 10);
	unArchivo->cargarBuffer();
	unArchivo->cargarBuffer();
	unArchivo->cargarBuffer();

	return 0;
}


