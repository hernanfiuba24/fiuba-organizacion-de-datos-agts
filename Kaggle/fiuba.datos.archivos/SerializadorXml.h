/*
 * SerializadorXml.h
 *
 *  Created on: 27/11/2014
 *      Author: HELLRAISER
 */
#include <vector>
#include <string>
#include "Markup.h"
#include "Parser.h"
#include "../fiuba.datos.ppmc/PPMC.h"
#include "../fiuba.datos.predictor/Frase.h"

#ifndef SERIALIZADORXML_H_
#define SERIALIZADORXML_H_

class SerializadorXml {
public:
	SerializadorXml();
	void Serializar(PPMC* ppmc, std::string path);
	Modelo0* DeserializarModelo0(std::string path);
	Modelo1* DeserializarModelo1(std::string path);
	ModelosSuperiores* DeserializarModelosSuperiores(unsigned numeroModelo, std::string path);
	void SerializarTestFile(std::vector<Frase*>* frasesCompletas, std::string path);
	virtual ~SerializadorXml();
	//Metodos de prueba--- BORRAR
	void ProbarDeserializador0(Modelo0* modelo);
	void ProbarDeserializador1(Modelo1* modelo);
	void ProbarDeserializadorSuperior(ModelosSuperiores* modelo);

private:
	void SerializarModelo0(Modelo0* modelo0, std::string path);
	void SerializarModelo1(Modelo1* modelo1, std::string path);
	void SerializarModelosSuperiores(ModelosSuperiores* modelo, std::string path);
	bool esUnContextoExistente(std::string nombreContexto);
	unsigned definirUmbral(unsigned numeroModelo);
    CMarkup xml;
};

#endif /* SERIALIZADORXML_H_ */
