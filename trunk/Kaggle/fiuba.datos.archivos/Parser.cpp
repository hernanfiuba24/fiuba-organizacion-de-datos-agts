/*
 * Parser.cpp
 *
 *  Created on: 10/11/2014
 *      Author: ezequiel
 */

#include <algorithm>
#include <iostream>
#include <string>
#include "Parser.h"
#include "BufferParser.h"
#include "../fiuba.datos.predictor/Frase.h"

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
	string contenidoTexto;
	string lineaTexto;
	std::getline(archivoTest, lineaTexto);
	int i = 1;
	while (std::getline(archivoTest, lineaTexto) && (i < 10))
	{
		contenidoTexto += lineaTexto;
		contenidoTexto.push_back('\n');
		i++;
	}

	return contenidoTexto;
}


vector<Frase*>* Parser::devolverFrases(string texto, char valorParseo){
	vector<Frase*>* palabrasParseadas = new vector<Frase*>;

	if (texto.length() > 0){
		stringstream stream(texto);
		string fraseTemporal = "";
		while (std::getline(stream, fraseTemporal, valorParseo)) {
			if (fraseTemporal.length() > 0){
				string textoFrase = fraseTemporal.substr(fraseTemporal.find_first_of(',') + 1, fraseTemporal.length() - 1);
				textoFrase = textoFrase.substr(1,textoFrase.length() - 2);
				Frase* nuevaFrase = new Frase(this->split(textoFrase,' '));
				palabrasParseadas->push_back(nuevaFrase);
			}
		}
	}
	return palabrasParseadas;
}


Parser::~Parser() {
	delete this->ultimasPalabras;
}

