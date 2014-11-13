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
	for(int i = 2; i<=(cantidadDeModelos); i++){
		int primo;
		if (i == 2)
			primo = 3001;
		else if (i == 3)
			primo = 6001;
		else if (i == 4)
			primo = 7001;
		else if (i == 5)
			primo = 8001; //ES POCO ESPACIO. 8001 SON MENOS DE 150K (SE PUDE AGREGAR MUCHO MAS)
		ModelosSuperiores* modeloi = new ModelosSuperiores(i, primo);
		this->modelosSuperiores->push_back(modeloi);
	}
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
	vector<string>* cincoPalabrasTemporales = this->devolverCincoPalabras(palabrasLimpias, 0, 4);

	string sarasa = "sarasa";

}

vector<string>* PPMC::devolverCincoPalabras(vector<string>* palabrasLimpias, int inicio, int fin){
	vector<string>* cincoPalabrasTemporales = new vector<string>;
	for (int i=inicio; i<=fin; i++){
		cincoPalabrasTemporales[i-inicio] = palabrasLimpias[i];
	}
	return cincoPalabrasTemporales;
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

