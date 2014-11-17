/*
 * Jenkins.cpp
 *
 *  Created on: 17/11/2014
 *      Author: hernan
 */

#include "Jenkins.h"

Jenkins::Jenkins() {
	// TODO Auto-generated constructor stub

}

uint32_t Jenkins::hashearCon32Bits(std::string nombre){

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

uint64_t Jenkins::hashearCon64Bits(std::string nombre){

	    uint64_t hash, i;
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
Jenkins::~Jenkins() {
	// TODO Auto-generated destructor stub
}

