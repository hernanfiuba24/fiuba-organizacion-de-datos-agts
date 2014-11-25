#ifndef FIUBA_DATOS_PPMC_PPMC_H_
#define FIUBA_DATOS_PPMC_PPMC_H_

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include "../fiuba.datos.ppmc/Modelo0.h"
#include "../fiuba.datos.ppmc/Modelo1.h"
#include "../fiuba.datos.ppmc/ModelosSuperiores.h"
#include "../fiuba.datos.ppmc/MapaFrecuencia.h"
#include "../fiuba.datos.ppmc/MapaContexto.h"


class PPMC {
private:
	    int cantidadDeModelos;
		Modelo0* modelo0; //ESTOS MODELOS HAY QUE GUARDARLOS EN
		Modelo1* modelo1; //MEMORIA, NO SE PERSISTEN
		ModelosSuperiores* modelosSuperiores[3];
		std::vector<std::string>* devolverPalabras(std::vector<std::string>* palabrasLimpias, int inicio, int fin, int cantPalabras);
		void cargarModelosSuperiores(std::vector<std::string>* cincoPalabrasTemporales, int cantidadDeModelos);
		void cargarModelo1(std::vector<std::string>* cincoPalabrasTemporales);
		void cargarModelo0(std::vector<std::string>* cincoPalabrasTemporales);
		void agregarContextoSuperiorEn(Contexto* unContexto, int numeroDeModelo);
		unsigned long devolverTamanioDeMapa(int numeroDeModelo);
		void  chequeoCasoParticular(std::vector<std::string>* palabrasLimpias, int inicio, unsigned tamanio, unsigned modelo, int iteraciones);

public:
	PPMC(int cantidadDeModelos);
	void guardarContextoEnModeloSuperior(int numeroDeModelo, Contexto *unContexto);
	void entrenar(std::string rutaArchivo);
	void entrenarPalabras(std::vector<std::string>* palabrasLimpias);
	Modelo0* getModelo0();
	ModelosSuperiores *getModelo4();
	void predecir(std::list<std::string>* frasesACompletar);
	~PPMC();
};

#endif
