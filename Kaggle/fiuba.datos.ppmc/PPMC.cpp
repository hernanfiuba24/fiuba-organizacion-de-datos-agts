#include "PPMC.h"

using namespace std;
#include <sys/time.h>


PPMC::PPMC(int cantidadDeModelos) {
	this->cantidadDeModelos = cantidadDeModelos;
	this->modelo0 = new Modelo0(1500001);
	this->modelo1 = new Modelo1(2000001, 1);
	for (int numeroDeModelo = 2; numeroDeModelo <= (cantidadDeModelos);
			numeroDeModelo++) {
		unsigned long tamanio = this->devolverTamanioDeMapa(numeroDeModelo);
		ModelosSuperiores* modelo = new ModelosSuperiores(tamanio,
				numeroDeModelo);
		this->modelosSuperiores[numeroDeModelo - 2] = modelo;
	}
}

Modelo0* PPMC::getModelo0() {
	return this->modelo0;
}

Modelo1* PPMC::getModelo1(){
	return this->modelo1;
}

ModelosSuperiores* PPMC::getModelo2(){
		return this->modelosSuperiores[0];
}

ModelosSuperiores* PPMC::getModelo3(){
	return this->modelosSuperiores[1];
}

ModelosSuperiores* PPMC::getModelo4() {
	return this->modelosSuperiores[2];
}

unsigned long PPMC::devolverTamanioDeMapa(int numeroDeModelo) {

	unsigned long primo;

	if (numeroDeModelo == 2)
		primo = 1000001;
	else if (numeroDeModelo == 3)
		primo = 2000001;
	else if (numeroDeModelo == 4)
		primo = 3000001;

	return primo;
}

void PPMC::entrenarPalabras(vector<string>* palabrasLimpias) {
	unsigned long tam = palabrasLimpias->size();
	string contexto, palabra;
	unsigned long inicio;
	int numeroModelo = 4;
	int cantPalabras = 5;
	//Modelos Superiores
	for(numeroModelo; numeroModelo >= 2; numeroModelo--){
		for (inicio = 0; inicio < (tam - numeroModelo); inicio++){
			contexto = this->devolverPalabras(palabrasLimpias, inicio, inicio+numeroModelo-1);
			palabra = (*palabrasLimpias)[inicio+numeroModelo];

//			cout<< "Contexto:" << contexto << '\t' << "Palabra:" <<palabra << endl;

			this->cargarModelosSuperiores(contexto, palabra, numeroModelo);

			if (palabra == ".")
				inicio += cantPalabras-1;
		}
		cantPalabras--;
	}
	//Modelo1 y Modelo0
	for (inicio = 0; inicio < (tam - numeroModelo); inicio++){
		contexto = this->devolverPalabras(palabrasLimpias, inicio, inicio+numeroModelo-1);
		palabra = (*palabrasLimpias)[inicio+numeroModelo];

//		cout<< "Contexto:" << contexto << '\t' << "Palabra:" <<palabra << endl;

		this->cargarModelo1(contexto, palabra);
		this->cargarModelo0(palabra);

		if (palabra == ".")
			inicio += 1;
	}
	//Tomo la primer palabra del vector que se saltea en el for anterior
	palabra = (*palabrasLimpias)[0];
	this->cargarModelo0(palabra);

	//Modelo0
//	cantPalabras--;
//	numeroModelo--;
//	for (inicio = 0; inicio < tam; inicio++){

//		palabra = (*palabrasLimpias)[inicio];

//		cout<< "Palabra:" <<palabra << endl;

//		this->cargarModelo0(palabra);
//	}

}

string PPMC::devolverPalabras(vector<string>* palabrasLimpias, unsigned long inicio, unsigned long fin) {
	string palabras;

	unsigned long i = inicio;
	palabras = (*palabrasLimpias)[i];
	i++;
	while (i <= fin) {
		palabras = palabras + " " + (*palabrasLimpias)[i];
		i++;
	}
	return palabras;
}

void PPMC::cargarModelosSuperiores(string contexto, string palabra, int numeroModelo) {

	if (numeroModelo == 4)
		this->cargarModelo4(contexto, palabra);
	else if (numeroModelo == 3)
		this->cargarModelo3(contexto, palabra);
	else if (numeroModelo == 2)
		this->cargarModelo2(contexto, palabra);

}

void PPMC::cargarModelo4(std::string contexto, std::string palabra){

	this->modelosSuperiores[2]->agregarContexto(contexto, palabra);
}

void PPMC::cargarModelo3(std::string contexto, std::string palabra){

	this->modelosSuperiores[1]->agregarContexto(contexto, palabra);
}

void PPMC::cargarModelo2(std::string contexto, std::string palabra){

	this->modelosSuperiores[0]->agregarContexto(contexto, palabra);
}

void PPMC::cargarModelo1(std::string contexto, std::string palabra) {

	this->modelo1->agregarContexto(contexto, palabra);
}

void PPMC::cargarModelo0(std::string palabra) {

	this->modelo0->agregarPalabra(palabra);
}

const std::string PPMC::currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

PPMC::~PPMC() {
	delete this->modelo0;
	delete this->modelo1;

	for(int i=0; i<=2; i++)
		delete this->modelosSuperiores[i];
}

