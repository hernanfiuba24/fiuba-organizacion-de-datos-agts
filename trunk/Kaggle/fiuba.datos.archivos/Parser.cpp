/*
 * Parser.cpp
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#include "Parser.h"
#include "Buffer.h"

using namespace std;

Parser::Parser() {
	this->ultimasPalabras = new list<string>;
	this->ultimaPalabra = 0;
}

list<string>* Parser::devolverPalabras(Buffer* buffer, char valorParseo) {
	list<string>* palabrasParseadas = new list<string>;
	string s(buffer->getBuffer());
	stringstream streamBuffer(s);
	string palabraTemporal = "";
	while (std::getline(streamBuffer, palabraTemporal, valorParseo)) {
		palabrasParseadas->push_back(palabraTemporal);
	}
	return palabrasParseadas;
}


list<string>* Parser::devolverFrases(string texto, char valorParseo){
	stringstream stream(texto);
	list<string>* palabrasParseadas = new list<string>;
	string fraseTemporal = "";
	while (std::getline(stream, fraseTemporal, valorParseo)) {
		palabrasParseadas->push_back(fraseTemporal.substr(fraseTemporal.find_first_of(',') + 1, fraseTemporal.length() - 1));
	}
	return palabrasParseadas;
}


Parser::~Parser() {
	delete[] this->ultimasPalabras;
}

