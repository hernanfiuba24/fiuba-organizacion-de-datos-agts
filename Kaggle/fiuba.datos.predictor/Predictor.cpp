/*
 * Predictor.cpp
 *
 *  Created on: 30/11/2014
 *      Author: ezequiel
 */

#include "Predictor.h"

using namespace std;

Predictor::Predictor() {
	this->completadorModelo4 = new vector<Completador*>;
	this->completadorModelo3 = new vector<Completador*>;
	this->completadorModelo2 = new vector<Completador*>;
	this->completadorModelo1 = new vector<Completador*>;
	this->completadorModelo0 = new vector<Completador*>;
}
//Paso el PPMC para ir cargando los modelos superiores
//( esto es solo para el momento de testeo)
void Predictor::completarFrases(vector<Frase* >* frasesACompletar, Modelo1* modelo1, Modelo0* modelo0, PPMC *unPPMC){

	this->completarFrecuencias(frasesACompletar, modelo1, modelo0, unPPMC);

	//BORRAR ESTO. SOLO PARA VER SI FUNCIONA BIEN!!!!!!!
	this->mostrarFrecuencias(frasesACompletar);

	this->cargarCompletadores(frasesACompletar);

	delete frasesACompletar;
	//Recorrer los completadorModelo.
	//Para el completadorModelo4 tengo el indice, el numeroDeFrase y la palabraConMayorFrec.
	//Accedo a la frase [numeroDeFrase] y agrego palabraConMayorFrecuencia en [indice]. Asi para todos.
	//Esto es lo que faltaria.

}

void Predictor::mostrarFrecuencias(vector<Frase*>* frasesACompletar){
	for(unsigned i = 0; i < frasesACompletar->size(); i++){
		vector< FrecuenciaModelo* >* frecuencias = (*frasesACompletar)[i]->getFrecuencias();
		cout << "Vector Frec:" << endl;
		for(unsigned i=0; i<frecuencias->size();i++){
			cout << (*frecuencias)[i]->getFrecuencia() << '\t' << (*frecuencias)[i]->getModelo() << '\t' << (*frecuencias)[i]->getPalabraConMayorFrecuencia() << endl;
		}
	}
}

void Predictor::completarFrecuencias(vector<Frase* >* frasesACompletar, Modelo1* modelo1, Modelo0* modelo0, PPMC *unPPMC){
		unsigned numeroModelo = 4;
		unsigned tamanioFrases = frasesACompletar->size();
		for (numeroModelo; numeroModelo >= 2; numeroModelo--) {

			//ModelosSuperiores* modeloSuperior = this->cargarModelosSuperiores(numeroModelo);
			ModelosSuperiores* modeloSuperior = this->ProvisoriaCargarModelosSuperiores(numeroModelo, unPPMC);
			for (unsigned i = 0; i < tamanioFrases; i++)
				this->predecirUnaFrase((*frasesACompletar)[i], modeloSuperior);
		//DESCOMENTAR ESTO DESPUES
			delete modeloSuperior;
		}

		for (unsigned i = 0; i < tamanioFrases; i++)
			this->predecirUnaFrase((*frasesACompletar)[i], modelo1);

		string palabraConMayorFrecuencia = modelo0->devolverPalabraConMayorFrecuencia();
		for (unsigned i = 0; i < tamanioFrases; i++)
				this->predecirUnaFrase((*frasesACompletar)[i], modelo0, palabraConMayorFrecuencia);

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
		//bool bajaDeNivel = (fraseACompletar->getModelo(numeroModelo, index) == NULL);
		float penalizacion;
		if ((!frecuenciaEsCero)){			//if ((!frecuenciaEsCero) && (bajaDeNivel)){
			penalizacion = modelosSuperiores->devolverPenalizacion(numeroModelo);
			fraseACompletar->setFrecuencia(penalizacion, frecuencia, numeroModelo, index);
			fraseACompletar->setModelo(numeroModelo, index);
			//Busca la palabra de mayor frecuencia para ese contexto
			//palabraConMayorFrecuencia this->buscarPalabraConMayorFrecuencia(contexto);
			fraseACompletar->setPalabraConMayorFrecuencia(modelosSuperiores, contexto, index, numeroModelo);

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
//		bool bajaDeNivel = (fraseACompletar->getModelo(numeroModelo, index) == NULL);
		float penalizacion;
		if ((!frecuenciaEsCero)){	//if ((!frecuenciaEsCero) && (bajaDeNivel)){
			penalizacion = modelo1->devolverPenalizacion();
			fraseACompletar->setFrecuencia(penalizacion, frecuencia, numeroModelo, index);
			fraseACompletar->setModelo(numeroModelo, index);
			fraseACompletar->setPalabraConMayorFrecuencia(modelo1, contexto, index, numeroModelo);
		}
	}
}

void Predictor::predecirUnaFrase(Frase* fraseACompletar, Modelo0* modelo0, string palabraConMayorFrecuencia){

	unsigned tam = fraseACompletar->getTamanioFrase();
	unsigned index = 1;
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
			fraseACompletar->setPalabraConMayorFrecuencia(palabraConMayorFrecuencia, index, numeroModelo);
		}
	}
}

void Predictor::cargarCompletadores(vector<Frase*>* frasesACompletar){

	for (int i=0; i < frasesACompletar->size(); i++){

		unsigned numeroFrase = i + 1;
		Completador *unCompletador = this->hallarLaFrecuenciaMinima((*frasesACompletar)[i], numeroFrase);
		this->setearCompletadorModelo(unCompletador);
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
		modeloSuperior = unSer->DeserializarModelosSuperiores(numeroModelo, "/home/matias/");
	else if (numeroModelo == 3 )
		modeloSuperior = unSer->DeserializarModelosSuperiores(numeroModelo, "/home/matias/");
	else if (numeroModelo == 4 )
		modeloSuperior = unSer->DeserializarModelosSuperiores(numeroModelo, "/home/matias/");

	return modeloSuperior;
}

ModelosSuperiores* Predictor::ProvisoriaCargarModelosSuperiores(unsigned numeroModelo, PPMC *unPPMC){

	 	ModelosSuperiores* modeloSuperior;

		if (numeroModelo == 2 )
			modeloSuperior = unPPMC->getModelo2();
		else if (numeroModelo == 3 )
			modeloSuperior = unPPMC->getModelo3();
		else if (numeroModelo == 4 )
			modeloSuperior = unPPMC->getModelo4();

		return modeloSuperior;
}

Completador* Predictor::hallarLaFrecuenciaMinima(Frase *fraseACompletar, unsigned numeroFrase){

	Completador* unComp = fraseACompletar->devolverFrecuenciaMinima(numeroFrase);
	return unComp;
}

void Predictor::setearCompletadorModelo(Completador* unCompletador){

	unsigned numeroModelo = unCompletador->getNumeroModelo();
	if (numeroModelo == 4)
		this->completadorModelo4->push_back(unCompletador);
	else if (numeroModelo == 3)
		this->completadorModelo3->push_back(unCompletador);
	else if (numeroModelo == 2)
		this->completadorModelo2->push_back(unCompletador);
	else if (numeroModelo == 1)
		this->completadorModelo1->push_back(unCompletador);
	else if (numeroModelo == 0)
		this->completadorModelo0->push_back(unCompletador);
}


Predictor::~Predictor() {
	delete this->completadorModelo0;
	delete this->completadorModelo1;
	delete this->completadorModelo2;
	delete this->completadorModelo3;
	delete this->completadorModelo4;
}

