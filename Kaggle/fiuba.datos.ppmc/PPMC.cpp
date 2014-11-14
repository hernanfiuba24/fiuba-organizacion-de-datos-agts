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
	this->modelo0 = new Modelo0(5001);
	this->modelo1 = new Modelo1(7001);
	this->modelosSuperiores = new list<ModelosSuperiores*>;
	for(int numeroDeModelo = 2; numeroDeModelo<=(cantidadDeModelos); numeroDeModelo++){
		int primo = this->devolverPrimo(numeroDeModelo);
		ModelosSuperiores* modelo = new ModelosSuperiores(numeroDeModelo, primo);
		this->modelosSuperiores->push_back(modelo);
	}
}

int PPMC::devolverPrimo(int numeroDeModelo){
	int primo;
		if (numeroDeModelo == 1)
			primo = 2001;
		else if (numeroDeModelo == 2)
			primo = 3001;
		else if (numeroDeModelo == 3)
			primo = 6001;
		else if (numeroDeModelo == 4)
			primo = 7001;
		else if (numeroDeModelo == 5)
			primo = 8001; //ES POCO ESPACIO. 8001 SON MENOS DE 150K (SE PUDE AGREGAR MUCHO MAS)

	return primo;
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


	int numeroDeModelo = this->modelosSuperiores->size();
	while (numeroDeModelo > 0){
		vector<string>::iterator it = cincoPalabrasTemporales->end();
		Palabra* ultimaPalabra = new Palabra(*it);
		string nombreContexto = "";
		for(it--; it >= cincoPalabrasTemporales->begin(); it--){
			nombreContexto = *it + " " + nombreContexto;
		}
		int primo = this->devolverPrimo(numeroDeModelo+1);

		//CADA CONTEXTO TIENE EL MISMO PRIMO QUE SU MODELO.
		//CONTROLAR ESTO PORQUE TAL VEZ NO SEA ASI.
		//TAL VEZ HAY QUE PONER UN PRIMO MAS CHICO

		Contexto* contextoSuperior = new Contexto(nombreContexto, primo);
		contextoSuperior->agregarPalabra(ultimaPalabra);
		this->agregarContextoSuperiorEn(contextoSuperior, numeroDeModelo);
		cincoPalabrasTemporales->pop_back();
		numeroDeModelo--;
	}
}

void PPMC::cargarModelo1(vector<string>* cincoPalabrasTemporales){

	vector<string>::iterator it = cincoPalabrasTemporales->end();

	Palabra* ultimaPalabra = new Palabra(*it);
	it--;
	int primo = this->devolverPrimo(1);
	Contexto* contextoModelo1 = new Contexto(*it, primo);
	contextoModelo1->agregarPalabra(ultimaPalabra);

	this->modelo1->agregarContexto(contextoModelo1);

	cincoPalabrasTemporales->pop_back();
}

void PPMC::cargarModelo0(vector<string>* cincoPalabrasTemporales){

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

