/*
 * Jenkins.cpp
 *
 *  Created on: 17/11/2014
 *      Author: hernan
 */

#include "Jenkins.h"

using namespace std;

Jenkins::Jenkins(unsigned primo){
	this->primo = primo;
}

uint32_t Jenkins::hashearCon32Bits(string nombre){

	    uint32_t hash, i;
	    int len = nombre.size();
	    for(hash = i = 0; i < len; ++i)
	    {
	        hash += nombre[i];
	        hash += (hash << 10);
	        hash ^= (hash >> 6);
	    }
	    hash += (hash << 3);
	    hash ^= (hash >> 11);
	    hash += (hash << 15);
	    return hash;

}

unsigned Jenkins::hashearConMod(string unNombre){
	uint32_t resultadoHash = this->hashearCon32Bits(unNombre);

	return resultadoHash % this->primo;
}

unsigned Jenkins::getPrimo(){
	return this->primo;
}

Jenkins::~Jenkins() {
}

