/*
 * HashingUniversalS.cpp
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#include "HashingUniversalS.h"

#include <iostream>

using namespace std;

HashingUniversalS::HashingUniversalS(unsigned int primo) {

	/* initialize random seed: */
	srand (time(NULL));

	this->primo = primo;

	this->a = rand() % this->primo;
	if (this->a != this->primo - 1 ){
		this->a+=1;
	}

	cout<<a;
}


int HashingUniversalS::hashString(string key){
	int resultadoHash=0;
	double  aux;
	int ascci;
    int tamanio = (int)key.length();
    int Hia = 0;
	for (unsigned int i=0; i < tamanio; i++){
		ascci = (int)key[i];
		aux = (ascci * pow( this->a, i+1)) + Hia;
		//Hia = aux % this->primo;
	}
	resultadoHash = Hia;
	return resultadoHash%this->primo;
}

