/*
 * Predictor.cpp
 *
 *  Created on: 30/11/2014
 *      Author: ezequiel
 */

#include "Predictor.h"

using namespace std;

Predictor::Predictor() {
	this->completadores = new vector<Completador*>;
}
//Paso el PPMC para ir cargando los modelos superiores
//( esto es solo para el momento de testeo)
void Predictor::completarFrases(vector<Frase* >* frasesACompletar, Modelo1* modelo1, Modelo0* modelo0, PPMC *unPPMC){

	this->completarFrecuencias(frasesACompletar, modelo1, modelo0, unPPMC);

	//BORRAR ESTO. SOLO PARA VER SI FUNCIONA BIEN!!!!!!!
	this->mostrarFrecuencias(frasesACompletar);

	this->cargarCompletadores(frasesACompletar);

	//delete frasesACompletar; //NO TENDRIA QUE BORRARLAS PORQUE SON LAS QUE TENGO QUE COMPLETAR!!! :s

	//Recorrer los completadorModelo.
	//Para el completadorModelo4 tengo el indice, el numeroDeFrase y la palabraConMayorFrec.
	//Accedo a la frase [numeroDeFrase] y agrego palabraConMayorFrecuencia en [indice]. Asi para todos.
	//Esto es lo que faltaria.
	this->completarPalabrasEnFrases(frasesACompletar);

	this->mostrarFrases(frasesACompletar);

}

void Predictor::mostrarFrases(vector<Frase*>* frasesACompletar){
	for(unsigned i = 0; i < frasesACompletar->size(); i++){
		vector<string>* frase = (*frasesACompletar)[i]->getFraseACompletar();
		cout << "Frase" << " " << i+1 << endl;
		for(vector<string>::iterator iter = frase->begin(); iter != frase->end(); ++iter){
			cout << (*iter) << " ";
		}
		cout << endl;
	}
}

void Predictor::mostrarFrecuencias(vector<Frase*>* frasesACompletar){
	for(unsigned i = 0; i < frasesACompletar->size(); i++){
		vector< FrecuenciaModelo* >* frecuencias = (*frasesACompletar)[i]->getFrecuencias();
		cout << "Vector Frec:" << endl;
		for(unsigned i=0; i<frecuencias->size();i++){
			cout << (*frecuencias)[i]->getFrecuencia() << '\t' << (*frecuencias)[i]->getPalabraConMayorFrecuencia() << endl;
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
		pair<unsigned long, bool>* frecExisteContexto;
		//unsigned long frecuencia = modelosSuperiores->devolverFrecuencia(contexto, palabra);
		frecExisteContexto = modelosSuperiores->devolverFrecuencia(contexto, palabra);
		bool frecuenciaEsCero = (frecExisteContexto->first == 0);
		//bool bajaDeNivel = (fraseACompletar->getModelo(numeroModelo, index) == NULL);
		float penalizacion;
		if(frecExisteContexto->second){

			fraseACompletar->setPalabraConMayorFrecuencia(modelosSuperiores, contexto, index, numeroModelo);
			if ((!frecuenciaEsCero)){			//if ((!frecuenciaEsCero) && (bajaDeNivel)){
				penalizacion = modelosSuperiores->devolverPenalizacion(numeroModelo);
				fraseACompletar->setFrecuencia(penalizacion, frecExisteContexto->first, numeroModelo, index);
				//fraseACompletar->setModelo(numeroModelo, index);
				//Busca la palabra de mayor frecuencia para ese contexto
				//palabraConMayorFrecuencia this->buscarPalabraConMayorFrecuencia(contexto);
			}
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
		pair<unsigned long, bool>* frecExisteContexto;
		//unsigned long frecuencia = modelo1->devolverFrecuencia(contexto, palabra);
		frecExisteContexto = modelo1->devolverFrecuencia(contexto, palabra);
		bool frecuenciaEsCero = (frecExisteContexto->second == 0);
//		bool bajaDeNivel = (fraseACompletar->getModelo(numeroModelo, index) == NULL);
		float penalizacion;
		if(frecExisteContexto->second){
				fraseACompletar->setPalabraConMayorFrecuencia(modelo1, contexto, index, numeroModelo);
				if ((!frecuenciaEsCero)){	//if ((!frecuenciaEsCero) && (bajaDeNivel)){
					penalizacion = modelo1->devolverPenalizacion();
					fraseACompletar->setFrecuencia(penalizacion, frecExisteContexto->first, numeroModelo, index);
					//fraseACompletar->setModelo(numeroModelo, index);
					//fraseACompletar->setPalabraConMayorFrecuencia(modelo1, contexto, index, numeroModelo);
				}
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
		//bool bajaDeNivel = (fraseACompletar->getModelo(numeroModelo, index) == NULL);
		float penalizacion;
		//if ((!frecuenciaEsCero) && (bajaDeNivel)){
			if (!frecuenciaEsCero){
			penalizacion = modelo0->devolverPenalizacion();
			fraseACompletar->setFrecuencia(penalizacion, frecuencia, numeroModelo, index);
			//fraseACompletar->setModelo(numeroModelo, index);
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

	this->completadores->push_back(unCompletador);
}

void Predictor::completarPalabrasEnFrases(vector<Frase* >* frasesACompletar){

	this->completarPalabrasDeLosCompletadores(frasesACompletar);
}

void Predictor::completarPalabrasDeLosCompletadores(vector<Frase* >* frasesACompletar){

	unsigned numeroFrase, posEnDondeCompletarFrase;
	string palabraMayorFrecuencia;
	// pido una sola ves la palabra con mayor frecuencia del modelo 0

	for(unsigned indice = 0; indice < this->completadores->size(); indice++){
		numeroFrase = (*this->completadores)[indice]->getNumeroFrase();
		posEnDondeCompletarFrase = (*this->completadores)[indice]->getPosEnDondeCompletarFrase();
		palabraMayorFrecuencia = (*this->completadores)[0]->getPalabraConMayorFrecuencia();
		(*frasesACompletar)[numeroFrase-1]->insertarPalabraEn(posEnDondeCompletarFrase, palabraMayorFrecuencia);
	}
}

Predictor::~Predictor() {
	unsigned tam = this->completadores->size();
	for(int i=0; i < tam; i++){
		delete (*this->completadores)[i];
	}
	delete this->completadores;
}
