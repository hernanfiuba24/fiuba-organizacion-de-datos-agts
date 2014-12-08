#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../fiuba.datos.ppmc/PPMC.h"
#include "../fiuba.datos.archivos/Archivo.h"
#include "../fiuba.datos.archivos/SerializadorXml.h"
#include "../fiuba.datos.predictor/Frase.h"
#include "../fiuba.datos.predictor/Predictor.h"
#include <time.h>

using namespace std;

void mostrarModelo(PPMC *unPPMC, int modelo) {

	/***************************************************************/
	/*************** PARA PROBAR EL PARSEO DEL TEST ****************/
//	Archivo* archivo = new Archivo();
//		vector<Frase*>* frases = archivo->parsearTest("/home/hellraiser/workspace/AGTS/test_v2.txt", '\n');
//
//		vector<Frase*>::iterator it = frases->begin();
//		cout << frases->size() << endl;
//		while (it != frases->end()){
//			vector<string>::iterator iter = (*it)->getFrase()->begin();
//			string fraseAux = "";
//			while (iter != (*it)->getFrase()->end()){
//				fraseAux += "  " + (*iter) + "  ";
//				iter++;
//			}
//			cout << fraseAux << endl;
//			it++;
//		}
	/***************************************************************/
	/***************************************************************/

	/* ESTO ES MUY RUSTICO. VAMOS ESCALANDO HASTA OBTENER EL "MAP"*/
	MapaContexto *unMapaContexto;
	Modelo1 *unModelo1;
	ModelosSuperiores *unModelo2;
	ModelosSuperiores *unModelo3;
	ModelosSuperiores *unModelo4;
	switch (modelo) {

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

	for (map<unsigned long, Contexto*>::const_iterator iterContexto =
			mapaHashCtx->begin(); iterContexto != mapaHashCtx->end();
			++iterContexto) {

		cout << iterContexto->first << '\t' << "MapaFrecuencia:";
		map<unsigned long, Palabra*>* mapaHashFrecuencia =
				iterContexto->second->getMapaFrecuencia()->getHashFrecuencia();
		for (map<unsigned long, Palabra*>::const_iterator iter2 =
				mapaHashFrecuencia->begin(); iter2 != mapaHashFrecuencia->end();
				++iter2) {
			cout << iter2->first << '\t' << iter2->second->getPalabra() << '\t'
					<< iter2->second->getFrecuencia() << " ";
		}
		cout << '\n';
	}
}

void mostrarModelo0(PPMC *unPPMC) {

	/* ESTO ESTA HECHO A LOS PONCHASOS. VASMOS ESCALANDO HASTA OBTENER EL "MAP"  */
	Modelo0* unModelo0 = unPPMC->getModelo0();
	MapaFrecuencia* unMapaF = unModelo0->getMapaFrecuencia();
	map<unsigned long, Palabra*>* mapaHashFrec = unMapaF->getHashFrecuencia();

	for (map<unsigned long, Palabra*>::const_iterator iter =
			mapaHashFrec->begin(); iter != mapaHashFrec->end(); ++iter)
		cout << iter->first << '\t' << iter->second->getPalabra() << '\t'
				<< iter->second->getFrecuencia() << '\n';
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

void entrenar(Archivo* unArchivo) {
	std::cout << "currentDateTime()=" << currentDateTime() << std::endl;

	cout << "Cargando Buffer..." << endl;
	unArchivo->cargarBuffer();
	cout << "Buffer cargado." << endl;
	cout << endl;

	cout << "Parseando Buffer..." << endl;
	vector<string>* palabrasLimpias = unArchivo->parsearBuffer(' ');
	cout << "Buffer PARSEADO" << endl;
	cout << endl;

	cout << "Entrenando..." << endl;
	PPMC* unPPMC = new PPMC(4);
	unPPMC->entrenarPalabras(palabrasLimpias);

	cout << "FIN Entrenado..." << endl;

	std::cout << "currentDateTime()=" << currentDateTime() << std::endl;

	cout << "Inicio Serializador" << endl;
	SerializadorXml* unSer = new SerializadorXml();
	unSer->Serializar(unPPMC, "/home/ezequiel/Documentos/Modelos/");
	cout << "Fin Serializar" << endl;

	std::cout << "currentDateTime()=" << currentDateTime() << std::endl;
	delete unPPMC;
	delete unSer;
}

void predecir() {

	SerializadorXml* unSer = new SerializadorXml();
	Predictor* unPred = new Predictor();

	Archivo* archivo = new Archivo();
	vector<Frase*>* frases = archivo->parsearTest(
			"/home/ezequiel/Documentos/Archivos/test_v2.txt", '\n');

	Modelo0 *unModelo0 = unSer->DeserializarModelo0(
			"/home/ezequiel/Documentos/Modelos/");
	Modelo1 *unModelo1 = unSer->DeserializarModelo1(
			"/home/ezequiel/Documentos/Modelos/");
	unPred->completarFrases(frases, unModelo1, unModelo0);

	unSer->SerializarTestFile(frases,
			"/home/ezequiel/Documentos/ArchivoCompletado/test_v2.txt");

	delete unSer;
	delete unPred;
	delete archivo;

	unsigned tamanioFrases = frases->size();
	for (unsigned i = 0; i < tamanioFrases; i++) {
		delete (*frases)[i];
	}
	delete frases;
}

/*             PROGRAMA PRINCIPAL                        */

int main() {
	//Cambiar los path por los que tengan en sus compus.
	//Hay uno en PREDICTOR en el metodo completarFrecuencias y despues todos aca en el main.
	unsigned opcionElegida;
	bool seguirEntrenando = true;
	bool salir = false;
	while (!salir) {
		cout << "Bienvinido a KaggleAGTS" << endl;
		cout << "Seleccione la opcion deseada:" << endl;
		cout << "1-Entrenar" << endl;
		cout << "2-Predecir" << endl;
		cout << "3-Salir" << endl;

		cin >> opcionElegida;

		switch (opcionElegida) {
		case 1: {
			if(!seguirEntrenando){
				cout << "Ya no puede entrenar mas." << endl;
				break;
			}
			unsigned cantidadAEntrenar;
			int inicioLectura;
			char seguir;
			cout << "Ingresar en bytes cuanta cantidad desea entrenar:" << endl;
			cin >> cantidadAEntrenar;
			cout << "Creando archivo" << endl;
			Archivo* unArchivo = new Archivo(
					"/home/ezequiel/Documentos/Archivos/train_v2.txt",
					cantidadAEntrenar);
			cout << "Archivo creado" << endl;
			cout << endl;
			while (seguirEntrenando) {
				cout << "Desde donde desea cargar(bytes):" << endl;
				cin >> inicioLectura;
				unArchivo->setInicioProximaLectura(inicioLectura);

				entrenar(unArchivo);
				cout << "¿Desea seguir entrenando?: s/n" << endl;
				cin >> seguir;
				seguirEntrenando = (seguir == 's');
			}
			delete unArchivo;
			break;
		}
		case 2: {
			cout << "Prediccion en curso..." << endl;
			cout<< "Aguarde un momento por favor.." << endl;

			std::cout << "currentDateTime()=" << currentDateTime() << std::endl;
			cout << endl;

			predecir();

			cout << "Fin prediccion! :) Pone el gancho HDRMP" << endl;

			std::cout << "currentDateTime()=" << currentDateTime() << std::endl;
			cout << endl;
			salir = true;
			break;
			}
		case 3:{
			salir = true;
		}
		}
	}
		return 0;
}

	/*	cout<< "Modelo 0:"<<endl;
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
	 cout << "Modelo 4:" << endl;
	 mostrarModelo(unPPMC, 4);*/
	/*	 cout << "Inicio Serializador" << endl;
	 SerializadorXml* unSer = new SerializadorXml();
	 unSer->Serializar(unPPMC);
	 cout << "Fin Serializar" << endl;

	 std::cout << "currentDateTime()=" << currentDateTime() << std::endl;

	 delete []palabrasLimpias;
	 return 0;
	 /******************************************************
	 //DESCOMENTAR ESTO PARA PROBAR PPMC*
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
	 palabrasLimpias->push_back("un");
	 palabrasLimpias->push_back("vector");
	 palabrasLimpias->push_back("re");
	 palabrasLimpias->push_back("loco");
	 palabrasLimpias->push_back(".");
	 palabrasLimpias->push_back("hola");
	 palabrasLimpias->push_back("como");
	 palabrasLimpias->push_back("estas");
	 palabrasLimpias->push_back("esto");
	 palabrasLimpias->push_back("es");
	 palabrasLimpias->push_back(".");
	 palabrasLimpias->push_back("la");
	 palabrasLimpias->push_back("casa");
	 palabrasLimpias->push_back("es");
	 palabrasLimpias->push_back("azul");
	 palabrasLimpias->push_back("y");
	 palabrasLimpias->push_back("lila");
	 palabrasLimpias->push_back(".");
	 palabrasLimpias->push_back("la");
	 palabrasLimpias->push_back("casa");
	 palabrasLimpias->push_back("es");
	 palabrasLimpias->push_back("blanca");
	 palabrasLimpias->push_back("y");
	 palabrasLimpias->push_back("lila");
	 palabrasLimpias->push_back(".");
	 palabrasLimpias->push_back("la");
	 palabrasLimpias->push_back("casa");
	 palabrasLimpias->push_back("es");
	 palabrasLimpias->push_back("blanca");
	 palabrasLimpias->push_back("y");
	 palabrasLimpias->push_back("azul");
	 palabrasLimpias->push_back(".");
	 palabrasLimpias->push_back("la");
	 palabrasLimpias->push_back("casa");
	 palabrasLimpias->push_back("es");
	 palabrasLimpias->push_back("blanca");
	 palabrasLimpias->push_back("y");
	 palabrasLimpias->push_back("roja");
	 palabrasLimpias->push_back(".");
	 palabrasLimpias->push_back("la");
	 palabrasLimpias->push_back("casa");
	 palabrasLimpias->push_back("es");
	 palabrasLimpias->push_back("blanca");
	 palabrasLimpias->push_back("y");
	 palabrasLimpias->push_back("violeta");
	 palabrasLimpias->push_back(".");
	 palabrasLimpias->push_back("la");
	 palabrasLimpias->push_back("casa");
	 palabrasLimpias->push_back("la");
	 palabrasLimpias->push_back("casa");
	 palabrasLimpias->push_back("es");
	 palabrasLimpias->push_back("blanca");
	 palabrasLimpias->push_back("y");
	 palabrasLimpias->push_back("lila");
	 palabrasLimpias->push_back(".");
	 palabrasLimpias->push_back("la");
	 palabrasLimpias->push_back("casa");
	 palabrasLimpias->push_back("es");
	 palabrasLimpias->push_back("rosa");
	 palabrasLimpias->push_back(",");
	 palabrasLimpias->push_back("blanca");
	 palabrasLimpias->push_back("y");
	 palabrasLimpias->push_back("lila");
	 palabrasLimpias->push_back(".");   */

//	mostrarModelo0(unPPMC);	 cout<<endl;
	/*cout<< "Modelo 0:"<<endl;
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
	 cout << "Modelo 4:" << endl;
	 mostrarModelo(unPPMC, 4);

	 cout << endl;
	 cout << endl;
	 */

	//  mostrarModelo(unPPMC, 4);
	/*	cout << endl;

	 vector<string>* frase1 = new vector<string>;

	 //investigators considered terrorism the likely cause.

	 frase1->push_back("Investigators");
	 frase1->push_back("considered");
	 frase1->push_back("terrorism");
	 frase1->push_back("likely");
	 frase1->push_back("cause");
	 frase1->push_back(".");

	 vector<string>* frase2 = new vector<string>;

	 // He was taken to York District Hospital , where he was pronounced dead .

	 frase2->push_back("He");
	 frase2->push_back("was");
	 frase2->push_back("taken");
	 frase2->push_back("York");
	 frase2->push_back("District");
	 frase2->push_back("Hospital");
	 frase2->push_back(",");
	 frase2->push_back("where");
	 frase2->push_back("he");
	 frase2->push_back("was");
	 frase2->push_back("pronounced");
	 frase2->push_back("dead");
	 frase2->push_back(".");

	 Frase* unaFrase1 = new Frase(frase1);
	 Frase* unaFrase2 = new Frase(frase2);

	 vector<Frase*>* frasesACompletar = new vector<Frase*>;
	 frasesACompletar->push_back(unaFrase1);
	 frasesACompletar->push_back(unaFrase2);

	 Predictor* unPred = new Predictor();
	 Modelo1 *unModelo1 = unPPMC->getModelo1();
	 Modelo0 *unModelo0 = unPPMC->getModelo0();
	 unPred->completarFrases(frasesACompletar, unModelo1, unModelo0, unPPMC);

	 //unPPMC->(frasesACompletar, 4);

	 return 0;

	 }*/
