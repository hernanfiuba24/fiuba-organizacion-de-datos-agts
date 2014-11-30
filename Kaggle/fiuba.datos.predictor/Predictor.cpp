/*
 * Predictor.cpp
 *
 *  Created on: 30/11/2014
 *      Author: ezequiel
 */

#include "Predictor.h"

using namespace std;

Predictor::Predictor() {

}

void Predictor::completarFrases(vector<Frase* >* frasesACompletar, Modelo1* modelo1, Modelo0* modelo0){

//FALTA TERMINAR!!!!
	unsigned numeroModelo = 4;
	for (numeroModelo; numeroModelo >= 2; numeroModelo--) {

		ModelosSuperiores* modeloSuperior = this->cargarModelosSuperiores(numeroModelo);
		for (int i = 0; i < frasesACompletar->size(); i++) {
			this->predecirUnaFrase((*frasesACompletar)[i], modeloSuperior);
		}
	//DESCOMENTAR ESTO DESPUES
		delete modeloSuperior;
/*	int i;
	float menorFrecuencia = (*frecuencias)[0].first;
	float frecTemporal;
	for(i = 1; i < frecuencias->size(); i++){
		frecTemporal = (*frecuencias)[i].first;
		if (menorFrecuencia > frecTemporal)
			menorFrecuencia = frecTemporal;
		}*/
//	parser.agregarFraseCompleta(id, frase);

	}

	for (int i = 0; i < frasesACompletar->size(); i++)
		this->predecirUnaFrase((*frasesACompletar)[i], modelo1);

	for (int i = 0; i < frasesACompletar->size(); i++)
			this->predecirUnaFrase((*frasesACompletar)[i], modelo0);
}

void Predictor::predecirUnaFrase(Frase* fraseACompletar, ModelosSuperiores* modelosSuperiores){

	unsigned tam = fraseACompletar->getTamanioFrase();
	unsigned index = 0;
	unsigned numeroModelo = modelosSuperiores->getNumeroModelo();
	for (index; index < tam - numeroModelo; index++) {

		string contexto = this->devolverContexto(fraseACompletar, numeroModelo, index+numeroModelo);
		string palabra = this->devolverPalabra(fraseACompletar, index, numeroModelo);

		unsigned long frecuencia = modelosSuperiores->devolverFrecuencia(contexto, palabra);
		bool frecuenciaEsCero = (frecuencia == 0);
		bool bajaDeNivel = (fraseACompletar->getModelo(numeroModelo, index) == NULL);
		float penalizacion;
		if ((!frecuenciaEsCero) && (bajaDeNivel)){
			penalizacion = modelosSuperiores->devolverPenalizacion(numeroModelo);
			fraseACompletar->setFrecuencia(penalizacion, frecuencia, numeroModelo, index);
			fraseACompletar->setModelo(numeroModelo, index);
		}
	}
}

void Predictor::predecirUnaFrase(Frase* fraseACompletar, Modelo1* modelo1){

	unsigned tam = fraseACompletar->getTamanioFrase();
	unsigned index = 0;
	unsigned numeroModelo = 1;
	for (index; index < tam - numeroModelo; index++) {

		string contexto = this->devolverContexto(fraseACompletar, numeroModelo, index+numeroModelo);
		string palabra = this->devolverPalabra(fraseACompletar, index, numeroModelo);

		unsigned long frecuencia = modelo1->devolverFrecuencia(contexto, palabra);
		bool frecuenciaEsCero = (frecuencia == 0);
		bool bajaDeNivel = (fraseACompletar->getModelo(numeroModelo, index) == NULL);
		float penalizacion;
		if ((!frecuenciaEsCero) && (bajaDeNivel)){
			penalizacion = modelo1->devolverPenalizacion();
			fraseACompletar->setFrecuencia(penalizacion, frecuencia, numeroModelo, index);
			fraseACompletar->setModelo(numeroModelo, index);
		}
	}
}

void Predictor::predecirUnaFrase(Frase* fraseACompletar, Modelo0* modelo0){

	unsigned tam = fraseACompletar->getTamanioFrase();
	unsigned index = 0;
	unsigned numeroModelo = 0;
	for (index; index < tam - numeroModelo; index++) {

		string palabra = this->devolverPalabra(fraseACompletar, index, numeroModelo);

		unsigned long frecuencia = modelo0->devolverFrecuencia(palabra);
		bool frecuenciaEsCero = (frecuencia == 0);
		bool bajaDeNivel = (fraseACompletar->getModelo(numeroModelo, index) == NULL);
		float penalizacion;
		if ((!frecuenciaEsCero) && (bajaDeNivel)){
			penalizacion = modelo0->devolverPenalizacion();
			fraseACompletar->setFrecuencia(penalizacion, frecuencia, numeroModelo, index);
			fraseACompletar->setModelo(numeroModelo, index);
		}
	}
}

string Predictor::devolverContexto(Frase* fraseACompletar, unsigned numeroModelo, unsigned inicio){

	return fraseACompletar->devolverContexto(numeroModelo, inicio);
}

string Predictor::devolverPalabra(Frase* fraseACompletar, unsigned numeroModelo, unsigned index){
	return fraseACompletar->devolverPalabra(index+numeroModelo);
}

ModelosSuperiores* Predictor::cargarModelosSuperiores(unsigned numeroModelo){

	ModelosSuperiores* modeloSuperior;

	SerializadorXml* unSer = new SerializadorXml();

	if (numeroModelo == 2 )
		modeloSuperior = unSer->DeserializarModelosSuperiores(numeroModelo);
	else if (numeroModelo == 3 )
		modeloSuperior = unSer->DeserializarModelosSuperiores(numeroModelo);
	else if (numeroModelo == 4 )
		modeloSuperior = unSer->DeserializarModelosSuperiores(numeroModelo);

	return modeloSuperior;
}




Predictor::~Predictor() {
}

