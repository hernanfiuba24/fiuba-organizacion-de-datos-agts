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
#include "Buffer.h"

class Parser {
public:
	Parser();
	int getPosultimaPalabra();
	std::list<std::string>* devolverPalabras(Buffer* buffer, char valorParseo);
	std::list<std::string>* devolverFrases(std::string texto, char valorParseo);
	virtual ~Parser();

private:
	std::list<std::string>* ultimasPalabras;
	char* ultimaPalabra;
};

#endif /* FIUBA_DATOS_ARCHIVOS_PARSER_H_ */
