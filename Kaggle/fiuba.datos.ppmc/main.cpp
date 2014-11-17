/*
 * main.cpp
 *
 *  Created on: 21/10/2014
 *      Author: Alumnos
 */

#include "PPMC.h"
#include <iostream>
#include <string>
#include <vector>
#include "../fiuba.datos.archivos/Archivo.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"
int main(){
	/*vector<std::string>* palabrasLimpias = new vector<std::string>;
	palabrasLimpias->push_back("hola");
	palabrasLimpias->push_back("como");
	palabrasLimpias->push_back("estas");
	palabrasLimpias->push_back("esto");
	palabrasLimpias->push_back("es");
	palabrasLimpias->push_back("un");
	palabrasLimpias->push_back("vector");
	palabrasLimpias->push_back("re");
	palabrasLimpias->push_back("loco");

	PPMC* unPPMC = new PPMC(4);

	unPPMC->entrenarPalabras(palabrasLimpias);
	*/
	//Archivo* unArchivo = new Archivo("/home/ezequiel/workspace/archivoPrueba.txt", 10);
	//unArchivo->cargarBuffer();

	//unArchivo->parsearBuffer();

	//unArchivo->cargarBuffer();

	//unArchivo->parsearBuffer();
	//delete unPPMC;
	//return 0;
	unsigned int primo = 5017;
	HashingUniversalS* unHash = new HashingUniversalS(primo);
	string palabra = "hola como estas";
	int indice = unHash->hashString(palabra);
}


