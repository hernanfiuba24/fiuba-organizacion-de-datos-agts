#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../fiuba.datos.ppmc/PPMC.h"
#include "../fiuba.datos.archivos/Archivo.h"
#include <time.h>

using namespace std;

void mostrarModelo(PPMC *unPPMC, int modelo){

	/* ESTO ES MUY RUSTICO. VAMOS ESCALANDO HASTA OBTENER EL "MAP"*/
	MapaContexto       *unMapaContexto;
	Modelo1            *unModelo1;
	ModelosSuperiores  *unModelo2;
	ModelosSuperiores  *unModelo3;
	ModelosSuperiores  *unModelo4;
	switch ( modelo ) {

	 	case 1:
			unModelo1 = unPPMC->getModelo1();
			unMapaContexto = unModelo1->getMapa();
			break;
	    case 2:
			unModelo2 = unPPMC->getModelo2();
			unMapaContexto = unModelo2->getMapa();
			break;
		case 3:
			unModelo3 = unPPMC->getModelo3();
			unMapaContexto = unModelo3->getMapa();
			break;
		case 4:
			unModelo4 = unPPMC->getModelo4();
			unMapaContexto = unModelo4->getMapa();
			break;
	}
	map<unsigned long, Contexto*>* mapaHashCtx = unMapaContexto->getMapaHash();

	for ( map<unsigned long, Contexto*>::const_iterator iterContexto = mapaHashCtx->begin();
		iterContexto != mapaHashCtx->end(); ++iterContexto ){

			cout << iterContexto->first << '\t' << "MapaFrecuencia:";
	        map<unsigned long,pair<string, unsigned> >* mapaHashFrecuencia = iterContexto->second->getMapaFrecuencia()->getHashFrecuencia();
	        for ( map<unsigned long, pair<string, unsigned> >::const_iterator iter2 = mapaHashFrecuencia->begin();
	        	iter2 != mapaHashFrecuencia->end(); ++iter2 ){
	        		cout << iter2->first << '\t' << iter2->second.first << '\t'  <<  iter2->second.second << " ";
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

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

/*             PROGRAMA PRINCIPAL                        */

int main(){
	std::cout << "currentDateTime()=" << currentDateTime() << std::endl;
	/*DESCOMENTAR ESTO PARA PROBAR PARSER*/
	//como tengo solo 1 G de Ram, solo voy leyendo de a 500Kb
	cout<< "Creando archivo"<<endl;
	Archivo* unArchivo = new Archivo("/home/ezequiel/Descargas/train_v2.txt", 100000000);
	cout<< "Archivo creado"<<endl;
	cout<<endl;
	cout<< "Cargando Buffer..."<<endl;
	unArchivo->cargarBuffer();
	cout<< "Buffer cargado."<<endl;
	cout<< endl;

	cout<< "Parseando Buffer..."<<endl;
	vector<string>* palabrasLimpias = unArchivo->parsearBuffer(' ');

	cout<< "Buffer PARSEADO"<<endl;
	cout<< endl;

	cout<< "Entrenando..."<<endl;
	PPMC* unPPMC = new PPMC(4);
	unPPMC->entrenarPalabras(palabrasLimpias);

	cout<< "FIN Entrenado..."<<endl;

	cout<<endl;
	cout<< "Modelo 0:"<<endl;
	mostrarModelo0(unPPMC);
	cout << endl;
	cout<< "Modelo 1:"<<endl;
	mostrarModelo(unPPMC, 1);
	cout << endl;
	cout<< "Modelo 2:"<<endl;
	mostrarModelo(unPPMC, 2);
	cout << endl;
	cout<< "Modelo 3:"<<endl;
	mostrarModelo(unPPMC, 3);
	cout << endl;
	cout<< "Modelo 4:"<<endl;
	mostrarModelo(unPPMC, 4);

	std::cout << "currentDateTime()=" << currentDateTime() << std::endl;

	delete []palabrasLimpias;
	return 0;
/******************************************************/
	/*DESCOMENTAR ESTO PARA PROBAR PPMC*
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

	list<string>* fraseACompletar = new list<string>;

	fraseACompletar->push_back("hola");
	fraseACompletar->push_back("como");
	fraseACompletar->push_back("estas");
	fraseACompletar->push_back("esto");
	fraseACompletar->push_back("es");
	fraseACompletar->push_back("un");
	fraseACompletar->push_back("re");
	fraseACompletar->push_back("loco");
	fraseACompletar->push_back(".");

	unPPMC->predecir(fraseACompletar, 4);

	return 0;

	*/

}
