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
	int resultadoHash;
	int acum = 0;


	for (int i=0; i < key.length(); i++){
		acum += (int)key[i]*pow( this->a, i+1);
	}

	return resultadoHash = acum % this->primo;
}

