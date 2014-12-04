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


SerializadorXml::~SerializadorXml() {}


void SerializadorXml::Serializar(PPMC* ppmc, std::string path){

	SerializarModelo0(ppmc->getModelo0(), path);
	SerializarModelo1(ppmc->getModelo1(), path);
	SerializarModelosSuperiores(ppmc->getModelo2(), path);
	SerializarModelosSuperiores(ppmc->getModelo3(), path);
	SerializarModelosSuperiores(ppmc->getModelo4(), path);

}


void SerializadorXml::SerializarModelo0(Modelo0* modelo0, std::string path){
	MapaFrecuencia* mapaFrecuencia = modelo0->getMapaFrecuencia();
	std::map<unsigned long, Palabra*>* hashFrecuencia = mapaFrecuencia->getHashFrecuencia();
	std::map<unsigned long, Palabra*>::iterator it = hashFrecuencia->begin();

	unsigned primoJenkins = modelo0->getJenkins()->getPrimo();
	this->xml.AddElem( "MODELO_0" );
	this->xml.SetAttrib("primoJenkins", primoJenkins);
	this->xml.IntoElem();

	unsigned int umbral = 0;
	while(it != hashFrecuencia->end()){
		unsigned long hashPalabra = (*it).first;
		string palabra = (*it).second->getPalabra();
		unsigned long int frecuencia = (*it).second->getFrecuencia();
		if (frecuencia > umbral){
			this->xml.AddElem("PALABRA");
			this->xml.SetAttrib("hash", hashPalabra);
			this->xml.SetAttrib("valor", palabra);
			this->xml.SetAttrib("frecuencia", frecuencia);
		}
		it++;

	}
	//Ruta Windows(No deberia existir): D:\\Modelo0.xml
	//Ruta UBUNTU: /home/ezequiel/Descargas/Modelo0.xml
	this->xml.OutOfElem();
	this->xml.Save( path + "Modelo_0.xml" );
	this->xml.RemoveElem();
}


void SerializadorXml::SerializarModelo1(Modelo1* modelo1, std::string path){
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
	this->xml.Save( path + "Modelo_1.xml" );
	this->xml.RemoveElem();
}


void SerializadorXml::SerializarModelosSuperiores(ModelosSuperiores* modelo, std::string path){
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

//		this->xml.AddElem( "CONTEXTO" );
//		this->xml.SetAttrib( "hash", hashContexto );
//		this->xml.SetAttrib( "primoJenkins", (*iterContexto).second->getJenkins()->getPrimo() );
//		this->xml.IntoElem();
		unsigned umbral = 0;
		bool puedoEntrar = true;
		while(iterPalabra != unContexto->end()){
			if ((*iterPalabra).second->getFrecuencia() > umbral){
				if (puedoEntrar){
					this->xml.AddElem( "CONTEXTO" );
					this->xml.SetAttrib( "hash", hashContexto );
					this->xml.SetAttrib( "primoJenkins", (*iterContexto).second->getJenkins()->getPrimo() );
					this->xml.IntoElem();
				}
				this->xml.AddElem( "PALABRA" );
				this->xml.SetAttrib( "hash", (*iterPalabra).first );
				this->xml.SetAttrib( "valor", (*iterPalabra).second->getPalabra() );
				this->xml.SetAttrib( "frecuencia", (*iterPalabra).second->getFrecuencia() );
				puedoEntrar = false;
			}
			iterPalabra++;
		}
		this->xml.OutOfElem();
		iterContexto++;
	}
	//Ruta en UBUNTU: /home/ezequiel/Descargas/Modelo_
	this->xml.OutOfElem();
	this->xml.Save( path + "Modelo_" + nroModeloString + ".xml" );
	this->xml.RemoveElem();
}


Modelo0* SerializadorXml::DeserializarModelo0(std::string path){

	unsigned long primo;
	unsigned long hashPalabra;
	int frecuenciaPalabra;
	xml.Load( path + "Modelo_0.xml" );
	xml.FindElem(); // root MODELO_X elemento

	stringstream(xml.GetAttrib("primoJenkins")) >> primo;
	Modelo0* modelo = new Modelo0(primo);

	xml.IntoElem(); // dentro MODELO_X

	while ( xml.FindElem("PALABRA") ){
		Palabra* palabra = new Palabra(xml.GetAttrib("valor"));
		stringstream(xml.GetAttrib("frecuencia")) >> frecuenciaPalabra;
		stringstream(xml.GetAttrib("hash")) >> hashPalabra;
		palabra->setFrecuencia(frecuenciaPalabra);
		modelo->setMapaFrecuencia(hashPalabra, palabra);
	}

	xml.OutOfElem();
	xml.RemoveElem();
	return modelo;
}


Modelo1* SerializadorXml::DeserializarModelo1(std::string path){
	unsigned long primoModelo;
	unsigned long primoContexto;
	unsigned long frecuenciaPalabra;
	unsigned long hashContexto;
	unsigned long hashPalabra;

	xml.Load( path + "Modelo_1.xml" );
	xml.FindElem(); // root MODELO_X elemento
	stringstream(xml.GetAttrib("primoJenkins")) >> primoModelo;
	Modelo1* unModelo1 = new Modelo1(primoModelo, 1);

	xml.IntoElem(); // dentro MODELO_X
	while ( xml.FindElem("CONTEXTO") ){
		stringstream(xml.GetAttrib("primoJenkins")) >> primoContexto;
		Contexto* unContexto = new Contexto(primoContexto);
		stringstream(xml.GetAttrib("hash")) >> hashContexto;

		xml.IntoElem(); // dentro CONTEXTO
		while (xml.FindElem("PALABRA")){
			Palabra* palabra = new Palabra(xml.GetAttrib("valor"));
			stringstream(xml.GetAttrib("frecuencia")) >> frecuenciaPalabra;
			stringstream(xml.GetAttrib("hash")) >> hashPalabra;
			palabra->setFrecuencia(frecuenciaPalabra);
			unContexto->setMapaFrecuencia(hashPalabra, palabra);
		}
		unModelo1->setMapaContexto(hashContexto, unContexto);
		xml.OutOfElem();
	}
	xml.OutOfElem();
	xml.RemoveElem();
	return unModelo1;
}


ModelosSuperiores* SerializadorXml::DeserializarModelosSuperiores(unsigned numeroModelo, std::string path){
	unsigned long primoModelo;
	unsigned long primoContexto;
	unsigned long frecuenciaPalabra;
	unsigned long hashContexto;
	unsigned long hashPalabra;

	stringstream ss;
	ss << numeroModelo;
	string nroModeloString = ss.str();

	xml.Load( path + "Modelo_" + nroModeloString + ".xml" );
	xml.FindElem(); // root MODELO_X elemento
	stringstream(xml.GetAttrib("primoJenkins")) >> primoModelo;
	ModelosSuperiores* unModeloSuperior = new ModelosSuperiores(primoModelo, numeroModelo);

	xml.IntoElem(); // dentro MODELO_X
	while ( xml.FindElem("CONTEXTO") ){
		stringstream(xml.GetAttrib("primoJenkins")) >> primoContexto;
		Contexto* unContexto = new Contexto(primoContexto);
		stringstream(xml.GetAttrib("hash")) >> hashContexto;

		xml.IntoElem(); // dentro CONTEXTO
		while (xml.FindElem("PALABRA")){
			Palabra* palabra = new Palabra(xml.GetAttrib("valor"));
			stringstream(xml.GetAttrib("frecuencia")) >> frecuenciaPalabra;
			stringstream(xml.GetAttrib("hash")) >> hashPalabra;
			palabra->setFrecuencia(frecuenciaPalabra);
			unContexto->setMapaFrecuencia(hashPalabra, palabra);
		}
		unModeloSuperior->setMapaContexto(hashContexto, unContexto);
		xml.OutOfElem();
	}
	xml.OutOfElem();
	xml.RemoveElem();
	return unModeloSuperior;
}

void SerializadorXml::SerializarTestFile(vector<Frase*>* frasesCompletas){
	string path = "/home/matias/testCompletado.txt";
	unsigned long idFrase = 1;
	ofstream fileTest;
	fileTest.open(path.c_str(), std::fstream::out);
	fileTest << "id,\"sentence\"\n";
	vector<Frase*>::iterator iteradorFrases = frasesCompletas->begin();
	while(iteradorFrases != frasesCompletas->end()){
		Frase* unaFrase = (*iteradorFrases);
		vector<string>* palabras = unaFrase->getFrase();
		vector<string>::iterator iteradorPalabras = palabras->begin();

		fileTest << idFrase << ",\"";
		while(iteradorPalabras != (*iteradorFrases)->getFrase()->end()){
			if (*iteradorPalabras != *((*iteradorFrases)->getFrase()->begin())){
				fileTest << " ";
			}
			fileTest << (*iteradorPalabras);

			iteradorPalabras++;
		}
		fileTest << "\"\n";
		iteradorFrases++;
		idFrase++;
	}
	fileTest.close();
}


void SerializadorXml::ProbarDeserializador0(Modelo0* modelo0){
	MapaFrecuencia* mapaFrecuencia = modelo0->getMapaFrecuencia();
	std::map<unsigned long, Palabra*>* hashFrecuencia = mapaFrecuencia->getHashFrecuencia();
	std::map<unsigned long, Palabra*>::iterator it = hashFrecuencia->begin();

	unsigned primoJenkins = modelo0->getJenkins()->getPrimo();
	this->xml.AddElem( "MODELO_0" );
	this->xml.SetAttrib("primoJenkins", primoJenkins);
	this->xml.IntoElem();

	unsigned int umbral = 0;
	while(it != hashFrecuencia->end()){
		unsigned long hashPalabra = (*it).first;
		string palabra = (*it).second->getPalabra();
		unsigned long int frecuencia = (*it).second->getFrecuencia();
		if (frecuencia > umbral){
			this->xml.AddElem("PALABRA");
			this->xml.SetAttrib("hash", hashPalabra);
			this->xml.SetAttrib("valor", palabra);
			this->xml.SetAttrib("frecuencia", frecuencia);
		}
		it++;

	}
	//Ruta Windows(No deberia existir): D:\\Modelo0.xml
	//Ruta UBUNTU: /home/ezequiel/Descargas/Modelo0.xml
	this->xml.OutOfElem();
	this->xml.Save( "C:\\Modelo_00.xml" );
	this->xml.RemoveElem();
}

void SerializadorXml::ProbarDeserializador1(Modelo1* modelo1){
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
	this->xml.Save( "C:\\Modelo_11.xml" );
	this->xml.RemoveElem();
}

void SerializadorXml::ProbarDeserializadorSuperior(ModelosSuperiores* modelo){
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

//		this->xml.AddElem( "CONTEXTO" );
//		this->xml.SetAttrib( "hash", hashContexto );
//		this->xml.SetAttrib( "primoJenkins", (*iterContexto).second->getJenkins()->getPrimo() );
//		this->xml.IntoElem();
		unsigned umbral = 0;
		bool puedoEntrar = true;
		while(iterPalabra != unContexto->end()){
			if ((*iterPalabra).second->getFrecuencia() > umbral){
				if (puedoEntrar){
					this->xml.AddElem( "CONTEXTO" );
					this->xml.SetAttrib( "hash", hashContexto );
					this->xml.SetAttrib( "primoJenkins", (*iterContexto).second->getJenkins()->getPrimo() );
					this->xml.IntoElem();
				}
				this->xml.AddElem( "PALABRA" );
				this->xml.SetAttrib( "hash", (*iterPalabra).first );
				this->xml.SetAttrib( "valor", (*iterPalabra).second->getPalabra() );
				this->xml.SetAttrib( "frecuencia", (*iterPalabra).second->getFrecuencia() );
				puedoEntrar = false;
			}
			iterPalabra++;
		}
		this->xml.OutOfElem();
		iterContexto++;
	}
	//Ruta en UBUNTU: /home/ezequiel/Descargas/Modelo_
	this->xml.OutOfElem();
	this->xml.Save( "C:\\Modelo_" + nroModeloString + nroModeloString + ".xml" );
	this->xml.RemoveElem();
}
