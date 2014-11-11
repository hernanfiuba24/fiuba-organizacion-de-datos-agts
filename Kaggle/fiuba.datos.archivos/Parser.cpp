/*
 * Parser.cpp
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#include "Parser.h"

using namespace std;

Parser::Parser() {
	this->ultimasPalabras = new list<char*>;
	this->ultimaPalabra = 0;
}

list<char*>* Parser::devolverPalabras(char* buffer){
	bool encontrePalabras = false;
	int contador = 0;
	size_t posicionActual = 0;
	string palabraTemporal;
	list<string>* palabrasParseadas;

	string palabra = "Hola Mundo";
	istringstream s2(palabra);

	while (s2 >> palabraTemporal) {
		palabrasParseadas->push_back(palabraTemporal);
	}
	cout<<palabrasParseadas->size();
		// print the vector
	for (list<string>::iterator it = palabrasParseadas->begin(); it != palabrasParseadas->end(); it++)
		cout << *it << endl;
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

