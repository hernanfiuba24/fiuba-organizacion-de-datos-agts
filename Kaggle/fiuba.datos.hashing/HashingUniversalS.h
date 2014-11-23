/*
 * HashingUniversalS.h
 *
 *  Created on: 6/11/2014
 *      Author: pc
 */

#ifndef HASHINGUNIVERSALS_H_
#define HASHINGUNIVERSALS_H_

#include <stdlib.h>		/* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <math.h>

class HashingUniversalS {
public:
	HashingUniversalS(unsigned int primo);

	int hashString(std::string key);

private:
	int a;
	unsigned int primo;
};

#endif /* HASHINGUNIVERSALS_H_ */
