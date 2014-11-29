/*
 * SerializadorXml.cpp
 *
 *  Created on: 27/11/2014
 *      Author: HELLRAISER
 */

#include "SerializadorXml.h"
#include "fiuba.datos.archivos/Parser.h"

using namespace std;

SerializadorXml::SerializadorXml() {
	this->parseador = new Parser();
}
void SerializadorXml::Serializar(std::string rutaArchivoOrigen, std::string rutaArchivoXml){

	string contenidoArchivoTxt = this->parseador->ParsearArchivoTxt(rutaArchivoOrigen);
	vector<string>* contextos = this->parseador->split(contenidoArchivoTxt, '\n');


	std::vector<std::string>::iterator it = contextos->begin();

	this->xml.AddElem( "MODELO" );
	this->xml.IntoElem();
	while(it != contextos->end()){
		vector<string>* contexto = parseador->split(string(*it),'\t');
		std::vector<std::string>::iterator iter = contexto->begin();

		if (contexto->size() >= 3){
			string hashPalabra = string(contexto->at(0));
			string palabra = string(contexto->at(1));
			string frecuencia = string(contexto->at(2));

			this->xml.AddElem( "CONTEXTO" );
			this->xml.SetAttrib( "hash", hashPalabra );
			this->xml.SetAttrib( "palabra", palabra );
			this->xml.SetAttrib( "frecuencia", frecuencia );
			it++;
		}
	}

	this->xml.OutOfElem();
	this->xml.Save( rutaArchivoXml.c_str() );

}


//bool SerializadorXml::esUnContextoExistente(std::string nombreContexto){
//
//}


SerializadorXml::~SerializadorXml() {
	delete[] this->parseador;
}
