/*
 * SerializadorXml.cpp
 *
 *  Created on: 27/11/2014
 *      Author: HELLRAISER
 */

#include "SerializadorXml.h"
#include "Parser.h"

using namespace std;

SerializadorXml::SerializadorXml() {
	//this->parseador = new Parser();
}
void SerializadorXml::Serializar(PPMC* ppmc){

	SerializarModelo0(ppmc->getModelo0());
	SerializarModelo1(ppmc->getModelo1());
//	string contenidoArchivoTxt = this->parseador->ParsearArchivoTxt(rutaArchivoOrigen);
//	vector<string>* contextos = this->parseador->split(contenidoArchivoTxt, '\n');
//
//
//	std::vector<std::string>::iterator it = contextos->begin();
//
//	this->xml.AddElem( "MODELO" );
//	this->xml.IntoElem();
//	while(it != contextos->end()){
//		vector<string>* contexto = parseador->split(string(*it),'\t');
//		std::vector<std::string>::iterator iter = contexto->begin();
//
//		if (contexto->size() >= 3){
//			string hashPalabra = string(contexto->at(0));
//			string palabra = string(contexto->at(1));
//			string frecuencia = string(contexto->at(2));
//
//			this->xml.AddElem( "CONTEXTO" );
//			this->xml.SetAttrib( "hash", hashPalabra );
//			this->xml.SetAttrib( "palabra", palabra );
//			this->xml.SetAttrib( "frecuencia", frecuencia );
//			it++;
//		}
//	}
//
//	this->xml.OutOfElem();
//	this->xml.Save( rutaArchivoXml.c_str() );

}

void SerializadorXml::SerializarModelo0(Modelo0* modelo0){
	MapaFrecuencia* mapaFrecuencia = modelo0->getMapaFrecuencia();
	std::map<unsigned long, Palabra*>* hashFrecuencia = mapaFrecuencia->getHashFrecuencia();
	std::map<unsigned long, Palabra*>::iterator it = hashFrecuencia->begin();

	this->xml.AddElem( "MODELO_0" );
	this->xml.IntoElem();

	while(it != hashFrecuencia->end()){
		unsigned long hashPalabra = (*it).first;
		string palabra = (*it).second->getPalabra();
		unsigned long int frecuencia = (*it).second->getFrecuencia();

		this->xml.AddElem("PALABRA");
		this->xml.SetAttrib("hash", hashPalabra);
		this->xml.SetAttrib("palabra", palabra);
		this->xml.SetAttrib("frecuencia", frecuencia);
		it++;
	}

	this->xml.OutOfElem();
	this->xml.Save( "C:\\modelo_0.xml" );

}

void SerializadorXml::SerializarModelo1(Modelo1* modelo1){
	this->xml.AddElem( "MODELO_1" );
	this->xml.IntoElem();

	std::map<unsigned long, Contexto*>* contextos = modelo1->getMapa()->getMapaHash();
	std::map<unsigned long, Contexto*>::iterator iterContexto = contextos->begin();

	while(iterContexto != contextos->end()){
		unsigned long hashContexto = (*iterContexto).first;
		std::map<unsigned long, Palabra*>* unContexto = (*iterContexto).second->getMapaFrecuencia()->getHashFrecuencia();
		std::map<unsigned long, Palabra*>::iterator iterPalabra = unContexto->begin();

		this->xml.AddElem( "CONTEXTO" );
		this->xml.SetAttrib( "hash", hashContexto );
		this->xml.IntoElem();

		while(iterPalabra != unContexto->end()){
			unsigned long hashPalabra = (*iterPalabra).first;
			int frecuenciaPalabra = (*iterPalabra).second->getFrecuencia();
			string valorPalabra = (*iterPalabra).second->getPalabra();

			this->xml.AddElem( "PALABRA" );
			this->xml.SetAttrib( "hash", hashPalabra );
			this->xml.SetAttrib( "valor", valorPalabra );
			this->xml.SetAttrib( "frecuencia", frecuenciaPalabra );

			iterPalabra++;
		}
		this->xml.OutOfElem();
		iterContexto++;
	}

	this->xml.OutOfElem();
	this->xml.Save( "C:\\Modelo_1.xml" );
}

SerializadorXml::~SerializadorXml() {
	//delete[] this->parseador;
}
