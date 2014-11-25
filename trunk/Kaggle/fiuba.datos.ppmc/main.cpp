#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../fiuba.datos.ppmc/PPMC.h"

using namespace std;

void mostrarModelo4(PPMC *unPPMC){

	/* ESTO ESTA HECHO A LOS PONCHASOS. VASMOS ESCALANDO HASTA OBTENER EL "MAP" */
    ModelosSuperiores* unModelo4 = unPPMC->getModelo4();
	MapaContexto* unMapaContexto = unModelo4->getMapa();
	map<unsigned long, Contexto*>* mapaHashCtx = unMapaContexto->getMapaHash();

	for ( map<unsigned long, Contexto*>::const_iterator iterContexto = mapaHashCtx->begin();
		iterContexto != mapaHashCtx->end(); ++iterContexto ){

			cout << iterContexto->first << '\t' << "MapaFrecuencia:";
	        map<unsigned long, pair<string, unsigned> >* mapaHashFrecuencia = iterContexto->second->getMapaFrecuencia()->getHashFrecuencia();
	        for ( map<unsigned long, pair<string, unsigned> >::const_iterator iter2 = mapaHashFrecuencia->begin();
	        	iter2 != mapaHashFrecuencia->end(); ++iter2 ){
	        	cout << iter2->first << '\t' << iter2->second.first << '\t' << iter2->second.second << "  ";
			}
            cout<< '\n';
	}
}

void mostrarModelo0(PPMC *unPPMC){

   /* ESTO ESTA HECHO A LOS PONCHASOS. VASMOS ESCALANDO HASTA OBTENER EL "MAP"  */
	Modelo0* unModelo0 = unPPMC->getModelo0();
	MapaFrecuencia* unMapaF = unModelo0->getMapaFrecuencia();
	map<unsigned long, pair<string, unsigned> >* mapaHashFrec = unMapaF->getHashFrecuencia();

	for ( map<unsigned long, pair<string, unsigned> >::const_iterator iter = mapaHashFrec->begin();
			iter != mapaHashFrec->end(); ++iter )
		    cout << iter->first << '\t' << iter->second.first << '\t' << iter->second.second << '\n';
}

/*             PROGRAMA PRINCIPAL                        */

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
	palabrasLimpias->push_back("hola");
	palabrasLimpias->push_back("como");
	palabrasLimpias->push_back("estas");
	palabrasLimpias->push_back("esto");
	palabrasLimpias->push_back("es");
	palabrasLimpias->push_back("loco");

	PPMC* unPPMC = new PPMC(4);
	unPPMC->entrenarPalabras(palabrasLimpias);

//    mostrarModelo0(unPPMC);

	cout << endl;
	cout << endl;

    mostrarModelo4(unPPMC);

	cout << endl;

	return 0;

}
