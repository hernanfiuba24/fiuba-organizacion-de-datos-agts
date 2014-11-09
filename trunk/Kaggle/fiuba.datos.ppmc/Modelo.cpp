#include "../fiuba.datos.ppmc/Modelo.h"
#include "../fiuba.datos.hashing/HashingUniversalS.h"

Modelo::Modelo(int numeroDeModelo){
	this->contextos = new list<Contexto>;
	this->numeroDeModelo = numeroDeModelo;
}

Modelo::~Modelo() {
	delete this->contextos;
}
void Modelo::agregarContexto(Contexto unContexto){
	int indice = this->hashearContexto(unContexto);

	std::list<Contexto>::iterator it;
	it = this->contextos->begin();
   	std::advance(it,indice);
   	this->contextos->insert(it, unContexto);
}

int Modelo::hashearContexto(Contexto unContexto){
	int p;
	if (this->numeroDeModelo = 2)
		p = 3001;
	else if (this->numeroDeModelo = 3)
		p = 6001;
	else if (this->numeroDeModelo = 4)
		p = 7001;
	else if (this->numeroDeModelo = 5)
		p = 8001; //ES POCO ESPACIO. 8001 SON MENOS DE 150K (SE PUDE AGREGAR MUCHO MAS)

	HashingUniversalS* unHash = new HashingUniversalS(p);
	return unHash->hashString(unContexto.getNombre());
}
