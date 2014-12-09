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
	cout<<"fin serializador modelo 0"<<endl;
	delete ppmc->getModelo0();
	SerializarModelo1(ppmc->getModelo1(), path);
	cout<<"fin serializador modelo 1"<<endl;
	delete ppmc->getModelo1();
	SerializarModelosSuperiores(ppmc->getModelo2(), path);
	cout<<"fin serializador modelo 2"<<endl;
	delete ppmc->getModelo2();
	SerializarModelosSuperiores(ppmc->getModelo3(), path);
	cout<<"fin serializador modelo 3"<<endl;
	delete ppmc->getModelo3();
	SerializarModelosSuperiores(ppmc->getModelo4(), path);
	cout<<"fin serializador modelo 4"<<endl;
	delete ppmc->getModelo4();
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
	delete auxModelo0;
}

void SerializadorXml::SerializarModelo1(Modelo1* modelo1, std::string path) {

	bool debeMergear;
	unsigned int umbral = 20;
	MapaContexto* auxMapaContexto;
	std::map<unsigned long, Contexto*>* auxHashContextos;
	Contexto *auxUnContexto;
	std::map<unsigned long, Palabra*>::iterator auxIterPalabra;

	Modelo1* auxModelo1 = DeserializarModelo1(path);
	debeMergear = (auxModelo1 != NULL);


	this->xml.AddElem("MODELO_1");
	this->xml.SetAttrib("primoJenkins", modelo1->getJenkins()->getPrimo());
	this->xml.IntoElem();

	map<unsigned long, Contexto*>* hashContextos = modelo1->getMapa()->getMapaHash();

	if (debeMergear){
		auxMapaContexto = auxModelo1->getMapa();
		auxHashContextos = auxMapaContexto->getMapaHash();

		this->mergearModeloConContexto(hashContextos, auxHashContextos, umbral);
	}
	else
	{	map<unsigned long, Contexto*>::iterator iterHashContexto = hashContextos->begin();

		unsigned long hashC;
		Contexto *unContexto;
		while (iterHashContexto != hashContextos->end()){
			hashC = (*iterHashContexto).first;
			unContexto = (*iterHashContexto).second;
			MapaFrecuencia *unMapaFrecuencia;
			map<unsigned long, Palabra*>* hashPalabra;
			unsigned long int primo = unContexto->getJenkins()->getPrimo();
			unMapaFrecuencia = unContexto->getMapaFrecuencia();
			hashPalabra = unMapaFrecuencia->getHashFrecuencia();

			this->noMergearModeloConContexto(hashPalabra,  umbral, primo, hashC);
			iterHashContexto++;

		}
	}

	this->xml.OutOfElem();
	this->xml.Save(path + "Modelo_1.xml");
	this->xml.RemoveElem();
	delete auxModelo1;
}

void SerializadorXml::SerializarModelosSuperiores(ModelosSuperiores* modelo, std::string path) {
	stringstream ss;
	ss << modelo->getNumeroModelo();
	string nroModeloString = ss.str();
	unsigned umbral = this->definirUmbral(modelo->getNumeroModelo());
	bool debeMergear;
	MapaContexto* auxMapaContexto;
	std::map<unsigned long, Contexto*>* auxHashContextos;
	Contexto *auxUnContexto;

	std::map<unsigned long, Palabra*>::iterator auxIterPalabra;
	ModelosSuperiores* auxModeloSuperior = DeserializarModelosSuperiores( modelo->getNumeroModelo(), path);
	debeMergear = (auxModeloSuperior != NULL);

	this->xml.AddElem("MODELO_"+ nroModeloString);
	this->xml.SetAttrib("primoJenkins", modelo->getJenkins()->getPrimo());
	this->xml.IntoElem();

	std::map<unsigned long, Contexto*>* hashContextos = modelo->getMapa()->getMapaHash();

	if (debeMergear){
		auxMapaContexto = auxModeloSuperior->getMapa();
		auxHashContextos = auxMapaContexto->getMapaHash();

		this->mergearModeloConContexto(hashContextos, auxHashContextos, umbral);
	}
	else
	{
		std::map<unsigned long, Contexto*>::iterator iterHashContexto = hashContextos->begin();

		unsigned long hashC;
		Contexto *unContexto;
		unsigned long int primo;
		while (iterHashContexto != hashContextos->end()){
			hashC = (*iterHashContexto).first;
			unContexto = (*iterHashContexto).second;
			MapaFrecuencia *unMapaFrecuencia;
			map<unsigned long, Palabra*>* hashPalabra;
			primo = unContexto->getJenkins()->getPrimo();
			unMapaFrecuencia = unContexto->getMapaFrecuencia();
			hashPalabra = unMapaFrecuencia->getHashFrecuencia();

			this->noMergearModeloConContexto(hashPalabra,  umbral, primo, hashC);

			iterHashContexto++;

		}
	}
	this->xml.OutOfElem();
	this->xml.Save(path + "Modelo_" + nroModeloString + ".xml");
	this->xml.RemoveElem();
	delete auxModeloSuperior;
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
	while ((it != hashFrecuencia->end()) || (auxIt != auxHashFrecuencia->end()) ){
				if(it == hashFrecuencia->end())
					hashPalabra = 1000000000;
				else
					hashPalabra = (*it).first;
				if(auxIt == auxHashFrecuencia->end())
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
}


void SerializadorXml::mergearModeloConContexto(std::map<unsigned long, Contexto*>* hashContexto, std::map<unsigned long, Contexto*>* auxHashContexto, unsigned int umbral){

	map<unsigned long, Contexto*>::iterator auxItHashContexto = auxHashContexto->begin();
	map<unsigned long, Contexto*>::iterator itHashContexto = hashContexto->begin();
	unsigned long int hashC;
	unsigned long int auxHashC;
	Contexto *unContexto;
	Contexto *auxUnContexto;
	unsigned long int primo;

	while ((itHashContexto != hashContexto->end()) || (auxItHashContexto != auxHashContexto->end()) ){

		MapaFrecuencia *unMapaFrecuencia;
		MapaFrecuencia *auxUnMapaFrecuencia;
		map<unsigned long, Palabra*>* hashFrecuencia;
		map<unsigned long, Palabra*>* auxHashFrecuencia;
		if(itHashContexto == hashContexto->end())
			hashC = 1000000000;
		else
			hashC = (*itHashContexto).first;
		if(auxItHashContexto == auxHashContexto->end())
			auxHashC = 1000000000;
		else
			auxHashC = (*auxItHashContexto).first;

		if(hashC < auxHashC){
			unMapaFrecuencia = (*itHashContexto).second->getMapaFrecuencia();
			hashFrecuencia = unMapaFrecuencia->getHashFrecuencia();
			primo = (*itHashContexto).second->getJenkins()->getPrimo();

			this->noMergearModeloConContexto(hashFrecuencia, umbral, primo, hashC);

			itHashContexto++;
		}
		else if(hashC > auxHashC){
			auxUnMapaFrecuencia = (*auxItHashContexto).second->getMapaFrecuencia();
			auxHashFrecuencia = auxUnMapaFrecuencia->getHashFrecuencia();
			primo = (*auxItHashContexto).second->getJenkins()->getPrimo();

			this->noMergearModeloConContexto(auxHashFrecuencia, umbral, primo, auxHashC);

			auxItHashContexto++;
		}
		else
		{	auxUnMapaFrecuencia = (*auxItHashContexto).second->getMapaFrecuencia();
			auxHashFrecuencia = auxUnMapaFrecuencia->getHashFrecuencia();
			unMapaFrecuencia = (*itHashContexto).second->getMapaFrecuencia();
			hashFrecuencia = unMapaFrecuencia->getHashFrecuencia();
			primo = (*itHashContexto).second->getJenkins()->getPrimo();
			this->xml.AddElem("CONTEXTO");
			this->xml.SetAttrib("hash", hashC);
			this->xml.SetAttrib("primoJenkins",primo);
			this->xml.IntoElem();
			this->mergearModelo0(hashFrecuencia, auxHashFrecuencia, umbral);
			this->xml.OutOfElem();
			itHashContexto++;
			auxItHashContexto++;
		}
	}
}

void SerializadorXml::noMergearModeloConContexto(map<unsigned long, Palabra*> *hashPalabra, unsigned int umbral, unsigned long int primo, unsigned long hashC){
	std::map<unsigned long, Palabra*>::iterator iterPalabra = hashPalabra->begin();
	bool puedoEntrar = true;
	while (iterPalabra != hashPalabra->end()) {
		unsigned long frecuenciaPalabra = (*iterPalabra).second->getFrecuencia();

		if (frecuenciaPalabra > umbral) {
			string nombrePalabra = (*iterPalabra).second->getPalabra();
			unsigned long hashPalabra = (*iterPalabra).first;

			if (puedoEntrar){
				// Serializo Contexto
				this->xml.AddElem("CONTEXTO");
				this->xml.SetAttrib("hash", hashC);
				this->xml.SetAttrib("primoJenkins",primo);
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
