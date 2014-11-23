#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../fiuba.datos.ppmc/PPMC.h"

using namespace std;
int main(){
	/*DESCOMENTAR ESTO PARA PROBAR PARSER*/
//	Archivo* unArchivo = new Archivo("C:\\train_v2.txt", 500);
//	unArchivo->cargarBuffer();
//	unArchivo->parsearBuffer(' ');

/******************************************************/

	/*DESCOMENTAR ESTO PARA PROBAR PPMC*/
	vector<string>* palabrasLimpias = new vector<string>;
		palabrasLimpias->push_back("hola");
		palabrasLimpias->push_back("como");
		palabrasLimpias->push_back("estas");
		palabrasLimpias->push_back("esto");
		palabrasLimpias->push_back("es");
		palabrasLimpias->push_back(".");
		palabrasLimpias->push_back("hola");
		palabrasLimpias->push_back("como");
		palabrasLimpias->push_back("estas");
		palabrasLimpias->push_back("esto");
		palabrasLimpias->push_back("es");
		palabrasLimpias->push_back(".");
		palabrasLimpias->push_back("vector");
		palabrasLimpias->push_back("re");
		palabrasLimpias->push_back("loco");
		palabrasLimpias->push_back("hola");
		palabrasLimpias->push_back("como");
		palabrasLimpias->push_back("estas");
		palabrasLimpias->push_back("esto");
		palabrasLimpias->push_back("es");
		palabrasLimpias->push_back(".");
		palabrasLimpias->push_back("loco");


	PPMC* unPPMC = new PPMC(4);
	unPPMC->entrenarPalabras(palabrasLimpias);

	Modelo0* unModelo0 = unPPMC->getModelo0();

	MapaFrecuencia* unMapaF = unModelo0->getMapaFrecuencia();

	map<unsigned,unsigned>* mapaHashFrec = unMapaF->getHashFrecuencia();

	for ( map<unsigned, unsigned>::const_iterator iter = mapaHashFrec->begin();
			iter != mapaHashFrec->end(); ++iter )
		    cout << iter->first << '\t' << iter->second << '\n';

		   cout << endl;
		   cout << endl;

	//	ModelosSuperiores* unModelo4 = unPPMC->getModelo4();

	//	map<unsigned, Contexto*>* mapaHashCtx = unModelo4->getMapa()->getMapaHash();


	//	for ( map<unsigned, Contexto*>::const_iterator iter = mapaHashCtx->begin();
		//		iter != mapaHashCtx->end(); ++iter ){
	//		   	cout << iter->first << '\t' << "MapaFrecuencia:";

	//		map<unsigned,unsigned>* mapaHashFrecuencia = iter->second->getMapaFrecuencia()->getHashFrecuencia();
	//		for ( map<unsigned, unsigned>::const_iterator iter2 = mapaHashFrecuencia->begin();
	//					iter2 != mapaHashFrecuencia->end(); ++iter2 ){
	//			cout << iter2->first << '\t' << iter2->second << '\n';
	//		}
	//	}


	cout << endl;

	return 0;

}
