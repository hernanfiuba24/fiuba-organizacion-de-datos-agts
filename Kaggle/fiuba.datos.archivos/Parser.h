/*
 * Parser.h
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#ifndef FIUBA_DATOS_ARCHIVOS_PARSER_H_
#define FIUBA_DATOS_ARCHIVOS_PARSER_H_

#include <string>
#include <list>
#include <sstream>
#include <iostream>

class Parser {
public:
	Parser();
	std::list<std::string>* devolverPalabras(char* buffer);
	virtual ~Parser();

private:
	std::list<std::string>* ultimasPalabras;
	char* ultimaPalabra;
};

#endif /* FIUBA_DATOS_ARCHIVOS_PARSER_H_ */
