/*
 * SerializadorXml.h
 *
 *  Created on: 27/11/2014
 *      Author: HELLRAISER
 */
#include <vector>
#include <string>
#include "Markup.h"
#include "fiuba.datos.archivos/Parser.h"

#ifndef SERIALIZADORXML_H_
#define SERIALIZADORXML_H_

class SerializadorXml {
public:
	SerializadorXml();
	void Serializar(std::string rutaArchivoOrigen, std::string rutaArchivoXml);
	std::vector<std::string>* DeserializarModelo(std::string numeroModelo);
	virtual ~SerializadorXml();

private:
	bool esUnContextoExistente(std::string nombreContexto);
    CMarkup xml;
	Parser* parseador;
};

#endif /* SERIALIZADORXML_H_ */
