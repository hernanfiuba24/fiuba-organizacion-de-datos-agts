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
}

SerializadorXml::~SerializadorXml() {
}

void SerializadorXml::Serializar(PPMC* ppmc, std::string path) {

	SerializarModelo0(ppmc->getModelo0(), path);
	/*SerializarModelo1(ppmc->getModelo1(), path);
	SerializarModelosSuperiores(ppmc->getModelo2(), path);
	SerializarModelosSuperiores(ppmc->getModelo3(), path);
	SerializarModelosSuperiores(ppmc->getModelo4(), path);
*/
}

void SerializadorXml::SerializarModelo0(Modelo0* modelo0, std::string path) {
	MapaFrecuencia* mapaFrecuencia = modelo0->getMapaFrecuencia();
	std::map<unsigned long, Palabra*>* hashFrecuencia = mapaFrecuencia->getHashFrecuencia();

	bool debeMergear;
	MapaFrecuencia* auxMapaFrecuencia;
	std::map<unsigned long, Palabra*>* auxHashFrecuencia;
	Modelo0* auxModelo0 = DeserializarModelo0(path);

	debeMergear = (auxModelo0 != NULL);

	unsigned primoJenkins = modelo0->getJenkins()->getPrimo();
	this->xml.AddElem("MODELO_0");
	this->xml.SetAttrib("primoJenkins", primoJenkins);
	this->xml.IntoElem();

	unsigned int umbral = 50;

	if (debeMergear){
		auxMapaFrecuencia = auxModelo0->getMapaFrecuencia();
		auxHashFrecuencia = auxMapaFrecuencia->getHashFrecuencia();
		this->mergearModelo0(hashFrecuencia, auxHashFrecuencia, umbral);
	}
	else{
		this->noMergearModelo0(hashFrecuencia, umbral);
	}
	this->xml.OutOfElem();
	this->xml.Save(path + "Modelo_0.xml");
	this->xml.RemoveElem();
}

void SerializadorXml::noMergearModelo0(std::map<unsigned long, Palabra*>* hashFrecuencia, unsigned int umbral){
	std::map<unsigned long, Palabra*>::iterator it = hashFrecuencia->begin();
	unsigned long int frecuencia;
	while (it != hashFrecuencia->end()) {
		unsigned long hashPalabra = (*it).first;
		string palabra = (*it).second->getPalabra();
		frecuencia = (*it).second->getFrecuencia();

		if (frecuencia > umbral) {
			this->xml.AddElem("PALABRA");
			this->xml.SetAttrib("hash", hashPalabra);
			this->xml.SetAttrib("palabra", palabra);
			this->xml.SetAttrib("frecuencia", frecuencia);
		}
		it++;
	}
}

void SerializadorXml::mergearModelo0(map<unsigned long, Palabra*>* hashFrecuencia, map<unsigned long, Palabra*>* auxHashFrecuencia, unsigned int umbral){
	std::map<unsigned long, Palabra*>::iterator auxIt = auxHashFrecuencia->begin();
	std::map<unsigned long, Palabra*>::iterator it = hashFrecuencia->begin();
	string palabra;
	unsigned long int frecuencia;
	unsigned long hashPalabra;
	unsigned long auxHashPalabra;
	unsigned long hash;
	while ((it != hashFrecuencia->end()) && (auxIt != auxHashFrecuencia->end()) ){
				if(it == hashFrecuencia->end())
					hashPalabra = 1000000000;
				else
					hashPalabra = (*it).first;
				if(it == auxHashFrecuencia->end())
					auxHashPalabra = 1000000000;
				else
					auxHashPalabra = (*auxIt).first;

				if(hashPalabra < auxHashPalabra){
					palabra = (*it).second->getPalabra();
					frecuencia = (*it).second->getFrecuencia();
					it++;
					hash = hashPalabra;
				}
				else if(hashPalabra > auxHashPalabra){
					palabra = (*auxIt).second->getPalabra();
					frecuencia = (*auxIt).second->getFrecuencia();
					auxIt++;
					hash = auxHashPalabra;
				}
				else{
					frecuencia = (*it).second->getFrecuencia();
					frecuencia += (*auxIt).second->getFrecuencia();
					palabra = (*it).second->getPalabra();
					hash = hashPalabra;
					it++;
					auxIt++;
				}
				if (frecuencia > umbral) {
					this->xml.AddElem("PALABRA");
					this->xml.SetAttrib("hash", hash);
					this->xml.SetAttrib("palabra", palabra);
					this->xml.SetAttrib("frecuencia", frecuencia);
				}
			}

	/*
	if (it == hashFrecuencia->end()){
		while (auxIt != auxHashFrecuencia->end()){
			auxHashPalabra = (*auxIt).first;
			palabra = (*auxIt).second->getPalabra();
			frecuencia = (*auxIt).second->getFrecuencia();
			this->xml.AddElem("PALABRA");
			this->xml.SetAttrib("hash", hash);
			this->xml.SetAttrib("palabra", palabra);
			this->xml.SetAttrib("frecuencia", frecuencia);
		}
	}
	else if (auxIt == auxHashFrecuencia->end()){

	}*/
}
void SerializadorXml::SerializarModelo1(Modelo1* modelo1, std::string path) {

	bool debeMergear;
	unsigned int umbral = 20;
	MapaContexto* auxMapaContexto;
	Contexto *auxUnContexto;
	std::map<unsigned long, Palabra*>::iterator auxIterPalabra;
	Modelo1* auxModelo1 = DeserializarModelo1(path);
	debeMergear = (auxModelo1 != NULL);
	if (debeMergear)
		auxMapaContexto = auxModelo1->getMapa();

	this->xml.AddElem("MODELO_1");
	this->xml.SetAttrib("primoJenkins", modelo1->getJenkins()->getPrimo());
	this->xml.IntoElem();

	std::map<unsigned long, Contexto*>* contextos =
			modelo1->getMapa()->getMapaHash();
	std::map<unsigned long, Contexto*>::iterator iterContexto =
			contextos->begin();

	while (iterContexto != contextos->end()) {

		unsigned long hashContexto = (*iterContexto).first;
		std::map<unsigned long, Palabra*>* unHashPalabra =
				(*iterContexto).second->getMapaFrecuencia()->getHashFrecuencia();
		std::map<unsigned long, Palabra*>::iterator iterPalabra =
				unHashPalabra->begin();

		bool existeContexto = false;
		if (debeMergear) {
			existeContexto = auxMapaContexto->existeClave(hashContexto);
			if (existeContexto) {
				auxUnContexto = auxMapaContexto->getContextos(hashContexto);
				auxIterPalabra =
						auxUnContexto->getMapaFrecuencia()->getHashFrecuencia()->begin();
			}
		}
		bool puedoEntrar = true;
		while (iterPalabra != unHashPalabra->end()) {

			string nombrePalabra = (*iterPalabra).second->getPalabra();
			unsigned long hashPalabra = (*iterPalabra).first;
			unsigned long frecuenciaPalabra =
					(*iterPalabra).second->getFrecuencia();
			unsigned long auxFrecuenciaPalabra = 0;

			if (debeMergear) {
				if (existeContexto){
					if (auxUnContexto->existePalabra(hashPalabra)) {
						auxFrecuenciaPalabra =	auxUnContexto->getMapaFrecuencia()->getFrecuencia(hashPalabra);
					}
				}
			}
			frecuenciaPalabra += auxFrecuenciaPalabra;

			if (frecuenciaPalabra > umbral) {
				if (puedoEntrar){
					// Serializo Contexto
					this->xml.AddElem("CONTEXTO");
					this->xml.SetAttrib("hash", hashContexto);
					this->xml.SetAttrib("primoJenkins",(*iterContexto).second->getJenkins()->getPrimo());
					this->xml.IntoElem();
				}
				this->xml.AddElem("PALABRA");
				this->xml.SetAttrib("hash", hashPalabra);
				this->xml.SetAttrib("valor", nombrePalabra);
				this->xml.SetAttrib("frecuencia", frecuenciaPalabra);
				puedoEntrar = false;
			}
			iterPalabra++;
		}
		if (!puedoEntrar)
			this->xml.OutOfElem();
		iterContexto++;
	}

	this->xml.OutOfElem();
	this->xml.Save(path + "Modelo_1.xml");
	this->xml.RemoveElem();
}

void SerializadorXml::SerializarModelosSuperiores(ModelosSuperiores* modelo,
		std::string path) {
	stringstream ss;
	ss << modelo->getNumeroModelo();
	string nroModeloString = ss.str();
	unsigned umbral = this->definirUmbral(modelo->getNumeroModelo());
	bool debeMergear;
	MapaContexto* auxMapaContexto;
	Contexto *auxUnContexto;

	std::map<unsigned long, Palabra*>::iterator auxIterPalabra;
	ModelosSuperiores* auxModeloSuperior = DeserializarModelosSuperiores(
			modelo->getNumeroModelo(), path);
	debeMergear = (auxModeloSuperior != NULL);
	if (debeMergear)
		auxMapaContexto = auxModeloSuperior->getMapa();

	this->xml.AddElem("MODELO_"+ nroModeloString);
	this->xml.SetAttrib("primoJenkins", modelo->getJenkins()->getPrimo());
	this->xml.IntoElem();

	std::map<unsigned long, Contexto*>* contextos =
			modelo->getMapa()->getMapaHash();
	std::map<unsigned long, Contexto*>::iterator iterContexto =
			contextos->begin();

	while (iterContexto != contextos->end()) {

		unsigned long hashContexto = (*iterContexto).first;
		std::map<unsigned long, Palabra*>* unHashPalabra =
				(*iterContexto).second->getMapaFrecuencia()->getHashFrecuencia();
		std::map<unsigned long, Palabra*>::iterator iterPalabra =
				unHashPalabra->begin();

		bool existeContexto = false;
		if (debeMergear) {
			existeContexto =auxMapaContexto->existeClave(hashContexto);
			if (existeContexto) {
				auxUnContexto = auxMapaContexto->getContextos(hashContexto);
				auxIterPalabra =
						auxUnContexto->getMapaFrecuencia()->getHashFrecuencia()->begin();
			}
		}
		bool puedoEntrar = true;
		while (iterPalabra != unHashPalabra->end()) {
			string nombrePalabra = (*iterPalabra).second->getPalabra();
			unsigned long hashPalabra = (*iterPalabra).first;
			unsigned long frecuenciaPalabra =
					(*iterPalabra).second->getFrecuencia();
			unsigned long auxFrecuenciaPalabra = 0;

			if (debeMergear) {
				if (existeContexto){
					if (auxUnContexto->existePalabra(hashPalabra)) {
						auxFrecuenciaPalabra = auxUnContexto->getMapaFrecuencia()->getFrecuencia(hashPalabra);
					}
				}
			}
			frecuenciaPalabra += auxFrecuenciaPalabra;

			if (frecuenciaPalabra > umbral){
				if (puedoEntrar){
					// Serializo Contexto
					this->xml.AddElem("CONTEXTO");
					this->xml.SetAttrib("hash", hashContexto);
					this->xml.SetAttrib("primoJenkins",(*iterContexto).second->getJenkins()->getPrimo());
					this->xml.IntoElem();
				}
				this->xml.AddElem("PALABRA");
				this->xml.SetAttrib("hash", hashPalabra);
				this->xml.SetAttrib("valor", nombrePalabra);
				this->xml.SetAttrib("frecuencia", frecuenciaPalabra);
				puedoEntrar = false;
			}
			iterPalabra++;
		}
		if(!puedoEntrar)
			this->xml.OutOfElem();
		iterContexto++;
	}
	this->xml.OutOfElem();
	this->xml.Save(path + "Modelo_" + nroModeloString + ".xml");
	this->xml.RemoveElem();
}

Modelo0* SerializadorXml::DeserializarModelo0(std::string path) {

	unsigned long primo;
	unsigned long hashPalabra;
	int frecuenciaPalabra;
	bool debeMergear = this->xml.Load(path + "Modelo_0.xml");
	if (debeMergear) {
		xml.FindElem(); // root MODELO_X elemento

		stringstream(xml.GetAttrib("primoJenkins")) >> primo;
		Modelo0* modelo = new Modelo0(primo);

		xml.IntoElem(); // dentro MODELO_X

		while (xml.FindElem("PALABRA")) {
			Palabra* palabra = new Palabra(xml.GetAttrib("palabra"));
			stringstream(xml.GetAttrib("frecuencia")) >> frecuenciaPalabra;
			stringstream(xml.GetAttrib("hash")) >> hashPalabra;
			palabra->setFrecuencia(frecuenciaPalabra);
			modelo->setMapaFrecuencia(hashPalabra, palabra);
		}
		xml.OutOfElem();
		xml.RemoveElem();
		return modelo;
	}
	return NULL;
}
Modelo1* SerializadorXml::DeserializarModelo1(std::string path) {
	unsigned long primoModelo;
	unsigned long primoContexto;
	unsigned long frecuenciaPalabra;
	unsigned long hashContexto;
	unsigned long hashPalabra;

	bool debeMergear = xml.Load(path + "Modelo_1.xml");

	if (debeMergear) {
		xml.FindElem(); // root MODELO_X elemento
		stringstream(xml.GetAttrib("primoJenkins")) >> primoModelo;
		Modelo1* unModelo1 = new Modelo1(primoModelo, 1);

		xml.IntoElem(); // dentro MODELO_X
		while (xml.FindElem("CONTEXTO")) {
			stringstream(xml.GetAttrib("primoJenkins")) >> primoContexto;
			Contexto* unContexto = new Contexto(primoContexto);
			stringstream(xml.GetAttrib("hash")) >> hashContexto;

			xml.IntoElem(); // dentro CONTEXTO
			while (xml.FindElem("PALABRA")) {
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
	return NULL;
}

ModelosSuperiores* SerializadorXml::DeserializarModelosSuperiores(
		unsigned numeroModelo, std::string path) {
	unsigned long primoModelo;
	unsigned long primoContexto;
	unsigned long frecuenciaPalabra;
	unsigned long hashContexto;
	unsigned long hashPalabra;

	stringstream ss;
	ss << numeroModelo;
	string nroModeloString = ss.str();

	bool debeMergear = xml.Load(path + "Modelo_" + nroModeloString + ".xml");
	if (debeMergear) {
		xml.FindElem(); // root MODELO_X elemento
		stringstream(xml.GetAttrib("primoJenkins")) >> primoModelo;
		ModelosSuperiores* unModeloSuperior = new ModelosSuperiores(primoModelo,
				numeroModelo);

		xml.IntoElem(); // dentro MODELO_X
		while (xml.FindElem("CONTEXTO")) {
			stringstream(xml.GetAttrib("primoJenkins")) >> primoContexto;
			Contexto* unContexto = new Contexto(primoContexto);
			stringstream(xml.GetAttrib("hash")) >> hashContexto;

			xml.IntoElem(); // dentro CONTEXTO
			while (xml.FindElem("PALABRA")) {
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
	return NULL;
}

void SerializadorXml::SerializarTestFile(vector<Frase*>* frasesCompletas, string path){
	unsigned long idFrase = 1;
	ofstream fileTest;
	fileTest.open(path.c_str(), std::fstream::out);
	fileTest << "id,\"sentence\"\n";
	vector<Frase*>::iterator iteradorFrases = frasesCompletas->begin();
	while (iteradorFrases != frasesCompletas->end()) {
		Frase* unaFrase = (*iteradorFrases);
		vector<string>* palabras = unaFrase->getFrase();
		vector<string>::iterator iteradorPalabras = palabras->begin();

		fileTest << idFrase << ",\"";
		while (iteradorPalabras != (*iteradorFrases)->getFrase()->end()) {
			if (*iteradorPalabras
					!= *((*iteradorFrases)->getFrase()->begin())) {
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

void SerializadorXml::ProbarDeserializador1(Modelo1* modelo1) {
	this->xml.AddElem("MODELO_1");
	this->xml.SetAttrib("primoJenkins", modelo1->getJenkins()->getPrimo());
	this->xml.IntoElem();

	std::map<unsigned long, Contexto*>* contextos =
	modelo1->getMapa()->getMapaHash();
	std::map<unsigned long, Contexto*>::iterator iterContexto =
	contextos->begin();

	while (iterContexto != contextos->end()) {
		unsigned long hashContexto = (*iterContexto).first;
		std::map<unsigned long, Palabra*>* unContexto =
		(*iterContexto).second->getMapaFrecuencia()->getHashFrecuencia();
		std::map<unsigned long, Palabra*>::iterator iterPalabra =
		unContexto->begin();

		this->xml.AddElem("CONTEXTO");
		this->xml.SetAttrib("hash", hashContexto);
		this->xml.SetAttrib("primoJenkins",
				(*iterContexto).second->getJenkins()->getPrimo());
		this->xml.IntoElem();

		while (iterPalabra != unContexto->end()) {

			this->xml.AddElem("PALABRA");
			this->xml.SetAttrib("hash", (*iterPalabra).first);
			this->xml.SetAttrib("valor", (*iterPalabra).second->getPalabra());
			this->xml.SetAttrib("frecuencia",
					(*iterPalabra).second->getFrecuencia());

			iterPalabra++;
		}
		this->xml.OutOfElem();
		iterContexto++;
	}

	this->xml.OutOfElem();
	this->xml.Save("C:\\Modelo_11.xml");
	this->xml.RemoveElem();
}

void SerializadorXml::ProbarDeserializadorSuperior(ModelosSuperiores* modelo) {
	stringstream ss;
	ss << modelo->getNumeroModelo();
	string nroModeloString = ss.str();

	this->xml.AddElem("MODELO_" + nroModeloString);
	this->xml.SetAttrib("primoJenkins", modelo->getJenkins()->getPrimo());
	this->xml.IntoElem();

	std::map<unsigned long, Contexto*>* contextos =
	modelo->getMapa()->getMapaHash();
	std::map<unsigned long, Contexto*>::iterator iterContexto =
	contextos->begin();

	while (iterContexto != contextos->end()) {
		unsigned long hashContexto = (*iterContexto).first;
		std::map<unsigned long, Palabra*>* unContexto =
		(*iterContexto).second->getMapaFrecuencia()->getHashFrecuencia();
		std::map<unsigned long, Palabra*>::iterator iterPalabra =
		unContexto->begin();

		unsigned umbral = 0;

		bool puedoEntrar = true;
		while (iterPalabra != unContexto->end()) {
			if ((*iterPalabra).second->getFrecuencia() > umbral) {
				if (puedoEntrar) {
					this->xml.AddElem("CONTEXTO");
					this->xml.SetAttrib("hash", hashContexto);
					this->xml.SetAttrib("primoJenkins",
							(*iterContexto).second->getJenkins()->getPrimo());
					this->xml.IntoElem();
				}
				this->xml.AddElem("PALABRA");
				this->xml.SetAttrib("hash", (*iterPalabra).first);
				this->xml.SetAttrib("valor",
						(*iterPalabra).second->getPalabra());
				this->xml.SetAttrib("frecuencia",
						(*iterPalabra).second->getFrecuencia());
				puedoEntrar = false;
			}
			iterPalabra++;
		}
		this->xml.OutOfElem();
		iterContexto++;
	}
	this->xml.OutOfElem();
	this->xml.Save("C:\\Modelo_" + nroModeloString + nroModeloString + ".xml");
	this->xml.RemoveElem();
}

unsigned SerializadorXml::definirUmbral(unsigned numeroModelo){
	unsigned umbral;
	if (numeroModelo == 4)
		umbral = 2;
	else if (numeroModelo == 3)
		umbral = 4;
	else if (numeroModelo == 2)
		umbral = 5;

	return umbral;
}
