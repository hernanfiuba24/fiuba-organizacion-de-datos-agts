/*
 * Parser.cpp
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#include "Parser.h"
#include "BufferParser.h"

using namespace std;

Parser::Parser() {
	this->ultimasPalabras = new vector<string>;
	this->ultimaPalabra = 0;
}
vector<string>* Parser::devolverPalabras(BufferParser* buffer, char valorParseo) {
	vector<string>* palabrasParseadas = new vector<string>;
	string s(buffer->getBuffer());
	stringstream streamBuffer(s);
	string palabraTemporal = "";
	while (std::getline(streamBuffer, palabraTemporal, valorParseo)) {
		palabrasParseadas->push_back(palabraTemporal);
	}
	return palabrasParseadas;
}

vector<string>* Parser::split(string texto, char valorParseo) {
	vector<string>* palabrasParseadas = new vector<string>;
	stringstream streamBuffer(texto);
	string palabraTemporal = "";
	while (std::getline(streamBuffer, palabraTemporal, valorParseo)) {
		palabrasParseadas->push_back(palabraTemporal);
	}
	return palabrasParseadas;
}


string Parser::ParsearArchivoTxt(string rutaArchivo){
	ifstream archivoTest(rutaArchivo.c_str(), ios::in);
	char c = archivoTest.get();
    string contenidoArchivoTxt = "";
	while (archivoTest.good()) {
		contenidoArchivoTxt += c;
		c = archivoTest.get();
	}

	return contenidoArchivoTxt;
}


vector<string>* Parser::devolverFrases(string texto, char valorParseo){
	stringstream stream(texto);
	vector<string>* palabrasParseadas = new vector<string>;
	string fraseTemporal = "";
	while (std::getline(stream, fraseTemporal, valorParseo)) {
		palabrasParseadas->push_back(fraseTemporal.substr(fraseTemporal.find_first_of(',') + 2, fraseTemporal.length() - 2));
	}
	return palabrasParseadas;
}


Parser::~Parser() {
	delete[] this->ultimasPalabras;
}

