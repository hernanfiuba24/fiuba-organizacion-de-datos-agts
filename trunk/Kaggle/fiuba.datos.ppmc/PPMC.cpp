/*
 * PPMC.cpp
 *
 *  Created on: 18/10/2014
 *      Author: ezequiel
 */

#include "PPMC.h"

using namespace std;

PPMC::PPMC(int cantidadDeModelos) {
	this->cantidadDeModelos = cantidadDeModelos;
	this->modelo0 = new Modelo0();
	this->modelo1 = new Modelo1();
	this->modelosSuperiores = new list<ModelosSuperiores*>;
	for(int numeroDeModelo = 2; numeroDeModelo<=(cantidadDeModelos); numeroDeModelo++){
		unsigned long tamanio = devolverTamanioDeTabla();
		tamanio = 50;
		ModelosSuperiores* modelo = new ModelosSuperiores(numeroDeModelo, tamanio);
		this->modelosSuperiores->push_back(modelo);
	}
}

unsigned long PPMC::devolverTamanioDeTabla(){

	unsigned long tamanio = pow(2,32);
	return tamanio;
}

void PPMC::entrenar(string rutaArchivo){
	ifstream setDeEntrenamiento;
	setDeEntrenamiento.open(rutaArchivo.c_str(), ios::in );	//NOSE QUE HACE C_STR() PERO SINO TIRA ERROR

	string linea;

	if (setDeEntrenamiento.is_open()){
		while ( getline(setDeEntrenamiento, linea)){
			cout << linea << endl;
		}
	setDeEntrenamiento.close();
	}
	else{
		//ESCRIBIR EXCEPCION POR SI EL ARCHIVO NO ABRE
	}
}

//CORREGIR ESTO VA A RECIBIR UN VECTOR<STRING>, NOSE CUANTAS PALABRAS VAN A VENIR
//TODO DEPENDE DEL PELA!!!!!!
void PPMC::entrenarPalabras(vector<string>* palabrasLimpias){
	int tamanio = palabrasLimpias->size();
	vector<string>* cincoPalabrasTemporales;
	for(int inicio = 0; inicio <= (tamanio - 5); inicio++){

		cincoPalabrasTemporales = this->devolverCincoPalabras(palabrasLimpias, inicio, inicio+4);

		this->cargarModelosSuperiores(cincoPalabrasTemporales);

		this->cargarModelo1(cincoPalabrasTemporales);
		this->cargarModelo0(cincoPalabrasTemporales);

		//CHEQUEO EL PUNTO PORQUE ME ROMPE LOS CONTEXTOS
		vector<string>::iterator it = cincoPalabrasTemporales->end();
		//VER SI ACA HAY QUE HACER it--
		if (*it == ".")
			inicio+=5;

	}
	delete cincoPalabrasTemporales;

}

vector<string>* PPMC::devolverCincoPalabras(vector<string>* palabrasLimpias, int inicio, int fin){
	vector<string>* cincoPalabrasTemporales = new vector<string>;
	int i = inicio;
	vector<string>::iterator it = palabrasLimpias->begin();
	advance(it,inicio);
	while (i <= fin){
		cincoPalabrasTemporales->push_back(*it);
		it++;
		i++;
	}
	cincoPalabrasTemporales->pop_back();
	return cincoPalabrasTemporales;
}

void PPMC::cargarModelosSuperiores(vector<string>* cincoPalabrasTemporales){

	//VOY BORRANDO LOS STRINGS QUE AGREGO A LOS MODELOS

	int numeroDeModelo = this->modelosSuperiores->size();
	while (numeroDeModelo > 0){
		vector<string>::iterator it = cincoPalabrasTemporales->end();
		Palabra* ultimaPalabra = new Palabra(*it);
		string nombreContexto = "";
		for(it--; it >= cincoPalabrasTemporales->begin(); it--){
			nombreContexto = *it + " " + nombreContexto;
		}

		Contexto* contextoSuperior = new Contexto(nombreContexto);
		contextoSuperior->agregarPalabra(ultimaPalabra);
		this->agregarContextoSuperiorEn(contextoSuperior, numeroDeModelo);
		cincoPalabrasTemporales->pop_back();
		numeroDeModelo--;
	}
}

void PPMC::cargarModelo1(vector<string>* cincoPalabrasTemporales){
	//EL VECTOR DE CINCO PALABRAS EN ESTE MOMENTO TIENE DOS ELEMENTOS
	//LOS PRIMEROS DOS
	vector<string>::iterator it = cincoPalabrasTemporales->end();

	Palabra* ultimaPalabra = new Palabra(*it);
	it--;
	Contexto* contextoModelo1 = new Contexto(*it);
	contextoModelo1->agregarPalabra(ultimaPalabra);

	this->modelo1->agregarContexto(contextoModelo1);

	cincoPalabrasTemporales->pop_back();
}

void PPMC::cargarModelo0(vector<string>* cincoPalabrasTemporales){
	//EL VECTOR DE CINCO PALABRAS EN ESTE MOMENTO TIENE UN SOLO ELEMENTO
	//EL ELEMENTO QUE QUEDA ES EL PRIMERO
	vector<string>::iterator it = cincoPalabrasTemporales->end();

	Palabra* ultimaPalabra = new Palabra(*it);
	this->modelo0->agregarPalabra(ultimaPalabra);
}

void PPMC::agregarContextoSuperiorEn(Contexto* unContexto, int numeroDeModelo){

	list<ModelosSuperiores*>::iterator it = this->modelosSuperiores->begin();

	advance(it,(numeroDeModelo - 1));

	ModelosSuperiores* modeloSuperior = *it;
	modeloSuperior->agregarContexto(unContexto);
}

PPMC::~PPMC() {
	delete this->modelo0;
	delete this->modelo1;
	for (int i=0; i<this->modelosSuperiores->size(); i++){
		list<ModelosSuperiores*>::iterator it;
	    it = this->modelosSuperiores->begin();
	    advance(it,i);
	    delete *it;
	}
	delete[] this->modelosSuperiores;
}

