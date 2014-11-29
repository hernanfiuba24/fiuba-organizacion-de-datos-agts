#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <iostream>
#include "BufferParser.h"

#ifndef Included_Parser_H
#define Included_Parser_H

class Parser {
public:
	Parser();
	int getPosultimaPalabra();
	std::vector<std::string>* devolverPalabras(BufferParser* buffer, char valorParseo);
	std::vector<std::string>* devolverFrases(std::string texto, char valorParseo);
	std::vector<std::string>* split(std::string texto, char valorParseo);
	std::string ParsearArchivoTxt(std::string rutaArchivo);
	virtual ~Parser();

private:
	std::vector<std::string>* ultimasPalabras;
	char* ultimaPalabra;
};

#endif // Included_Parser_H
