#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <iostream>
#include "BufferParser.h"

class Parser {
public:
	Parser();
	int getPosultimaPalabra();
	std::vector<std::string>* devolverPalabras(BufferParser* buffer, char valorParseo);
	std::vector<std::string>* devolverFrases(std::string texto, char valorParseo);
	virtual ~Parser();

private:
	std::vector<std::string>* ultimasPalabras;
	char* ultimaPalabra;
};

