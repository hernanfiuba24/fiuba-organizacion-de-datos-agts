/*
 * Jenkins.h
 *
 *  Created on: 17/11/2014
 *      Author: hernan
 */

#ifndef FIUBA_DATOS_HASHING_JENKINS_H_
#define FIUBA_DATOS_HASHING_JENKINS_H_

#include <iostream>
#include "stdint.h"
#include <math.h>

class Jenkins {
public:
	Jenkins(unsigned primo);
	unsigned hashearConMod(std::string nombre);
	virtual ~Jenkins();
private:
	uint32_t hashearCon32Bits(std::string nombre);
	unsigned primo;
};

#endif /* FIUBA_DATOS_HASHING_JENKINS_H_ */
