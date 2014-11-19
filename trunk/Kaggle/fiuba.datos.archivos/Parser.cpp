/*
 * Parser.cpp
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#include "Parser.h"

using namespace std;

Parser::Parser() {
	this->ultimasPalabras = new list<string>;
	this->ultimaPalabra = 0;
}

list<string>* Parser::devolverPalabras(char* buffer, char valorParseo){
	list<string>* palabrasParseadas = new list<string>;
	string s(buffer);
	stringstream streamBuffer(s);
	string palabraTemporal;
	while (std::getline(streamBuffer, palabraTemporal, ' ')) {
	palabrasParseadas->push_back(palabraTemporal);
	}
	list<string>::iterator it = palabrasParseadas->begin();

	while(it != palabrasParseadas->end()){
		cout << *it << endl;
		it++;
	}

	return palabrasParseadas;
}

Parser::~Parser() {
	delete[] this->ultimasPalabras;
}

