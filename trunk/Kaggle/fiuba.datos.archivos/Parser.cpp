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

list<string>* Parser::devolverPalabras(char* buffer){

	list<string>* palabrasParseadas = new list<string>;
	string palabraTemporal;

	istringstream s2(buffer);

	while (s2 >> palabraTemporal) {
		palabrasParseadas->push_back(palabraTemporal);
	}
	cout<<palabrasParseadas->size();
		// print the vector
	for (list<string>::iterator it = palabrasParseadas->begin(); it != palabrasParseadas->end(); it++)
		cout << *it << endl;

	return palabrasParseadas;
}

Parser::~Parser() {
	delete[] this->ultimasPalabras;
}

