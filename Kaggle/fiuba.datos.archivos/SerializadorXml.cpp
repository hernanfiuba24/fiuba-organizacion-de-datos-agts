/*
 * SerializadorXml.cpp
 *
 *  Created on: 27/11/2014
 *      Author: HELLRAISER
 */

#include "SerializadorXml.h"
#include "Parser.h"

using namespace std;

SerializadorXml::SerializadorXml() {}


void SerializadorXml::Serializar(PPMC* ppmc){

	SerializarModelo0(ppmc->getModelo0());
	SerializarModelo1(ppmc->getModelo1());
	SerializarModelosSuperiores(ppmc->getModelo2());
	SerializarModelosSuperiores(ppmc->getModelo3());
	SerializarModelosSuperiores(ppmc->getModelo4());

}


void SerializadorXml::SerializarModelo0(Modelo0* modelo0){
	MapaFrecuencia* mapaFrecuencia = modelo0->getMapaFrecuencia();
	std::map<unsigned long, Palabra*>* hashFrecuencia = mapaFrecuencia->getHashFrecuencia();
	std::map<unsigned long, Palabra*>::iterator it = hashFrecuencia->begin();

	this->xml.AddElem( "MODELO_0" );
	this->xml.IntoElem();

	while(it != hashFrecuencia->end()){
		unsigned primoJenkins = modelo0->getJenkins()->getPrimo();
		unsigned long hashPalabra = (*it).first;
		string palabra = (*it).second->getPalabra();
		unsigned long int frecuencia = (*it).second->getFrecuencia();

		this->xml.AddElem("PALABRA");
		this->xml.SetAttrib("primoJenkins", primoJenkins);
		this->xml.SetAttrib("hash", hashPalabra);
		this->xml.SetAttrib("palabra", palabra);
		this->xml.SetAttrib("frecuencia", frecuencia);
		it++;
	}

	this->xml.OutOfElem();
	this->xml.Save( "C:\\modelo_0.xml" );
	this->xml.RemoveElem();
}


void SerializadorXml::SerializarModelo1(Modelo1* modelo1){
	this->xml.AddElem( "MODELO_1" );
	this->xml.SetAttrib( "primoJenkins", modelo1->getJenkins()->getPrimo() );
	this->xml.IntoElem();

	std::map<unsigned long, Contexto*>* contextos = modelo1->getMapa()->getMapaHash();
	std::map<unsigned long, Contexto*>::iterator iterContexto = contextos->begin();

	while(iterContexto != contextos->end()){
		unsigned long hashContexto = (*iterContexto).first;
		std::map<unsigned long, Palabra*>* unContexto = (*iterContexto).second->getMapaFrecuencia()->getHashFrecuencia();
		std::map<unsigned long, Palabra*>::iterator iterPalabra = unContexto->begin();

		this->xml.AddElem( "CONTEXTO" );
		this->xml.SetAttrib( "hash", hashContexto );
		this->xml.SetAttrib( "primoJenkins", (*iterContexto).second->getJenkins()->getPrimo() );
		this->xml.IntoElem();

		while(iterPalabra != unContexto->end()){

			this->xml.AddElem( "PALABRA" );
			this->xml.SetAttrib( "hash", (*iterPalabra).first );
			this->xml.SetAttrib( "valor", (*iterPalabra).second->getPalabra() );
			this->xml.SetAttrib( "frecuencia", (*iterPalabra).second->getFrecuencia() );

			iterPalabra++;
		}
		this->xml.OutOfElem();
		iterContexto++;
	}

	this->xml.OutOfElem();
	this->xml.Save( "C:\\Modelo_1.xml" );
	this->xml.RemoveElem();
}


void SerializadorXml::SerializarModelosSuperiores(ModelosSuperiores* modelo){
	stringstream ss;
	ss << modelo->getNumeroModelo();
	string nroModeloString = ss.str();

	this->xml.AddElem( "MODELO_" + nroModeloString );
	this->xml.SetAttrib( "primoJenkins", modelo->getJenkins()->getPrimo() );
	this->xml.IntoElem();

	std::map<unsigned long, Contexto*>* contextos = modelo->getMapa()->getMapaHash();
	std::map<unsigned long, Contexto*>::iterator iterContexto = contextos->begin();

	while(iterContexto != contextos->end()){
		unsigned long hashContexto = (*iterContexto).first;
		std::map<unsigned long, Palabra*>* unContexto = (*iterContexto).second->getMapaFrecuencia()->getHashFrecuencia();
		std::map<unsigned long, Palabra*>::iterator iterPalabra = unContexto->begin();

		this->xml.AddElem( "CONTEXTO" );
		this->xml.SetAttrib( "hash", hashContexto );
		this->xml.SetAttrib( "primoJenkins", (*iterContexto).second->getJenkins()->getPrimo() );
		this->xml.IntoElem();

		while(iterPalabra != unContexto->end()){

			this->xml.AddElem( "PALABRA" );
			this->xml.SetAttrib( "hash", (*iterPalabra).first );
			this->xml.SetAttrib( "valor", (*iterPalabra).second->getPalabra() );
			this->xml.SetAttrib( "frecuencia", (*iterPalabra).second->getFrecuencia() );

			iterPalabra++;
		}
		this->xml.OutOfElem();
		iterContexto++;
	}

	this->xml.OutOfElem();
	this->xml.Save( "C:\\Modelo_" + nroModeloString + ".xml" );
	this->xml.RemoveElem();
}


SerializadorXml::~SerializadorXml() {}
