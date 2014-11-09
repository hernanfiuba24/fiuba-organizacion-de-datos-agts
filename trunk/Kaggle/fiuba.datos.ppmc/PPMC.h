/*
 * PPMC.h
 *
 *  Created on: 18/10/2014
 *      Author: ezequiel
 */
#ifndef FIUBA_DATOS_PPMC_PPMC_H_
#define FIUBA_DATOS_PPMC_PPMC_H_

#include <list>
#include "Modelo.h"
#include "Modelo0.h"
#include "Modelo1.h"
#include <iostream>
#include <fstream>

using namespace std;

class PPMC {
private:
		Modelo0* modelo0; //ESTOS MODELOS HAY QUE GUARDARLOS EN
		Modelo1* modelo1; //MEMORIA, NO SE PERSISTEN
		list<Modelo*> modelosSuperiores;

public:
	PPMC(int cantidadDeModelos);
	void entrenar(string rutaArchivo);
	~PPMC();
};

#endif
