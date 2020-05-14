#ifndef WORKER_PROCESSOR_H
#define WORKER_PROCESSOR_H

#include <vector>
#include <string>
#include "worker.h"
#include "protected_queue.h"
#include "protected_inventory.h"
#include "protected_points.h"

class UnknownWorkerException : public std::exception {
public:
	const char *what() const throw();
};

class WorkerCountException : public std::exception {
public:
	const char *what() const throw();
};

class WorkerProcessor {
private:
	std::vector<Worker*> &farmers;
	std::vector<Worker*> &lumberjacks;
	std::vector<Worker*> &miners;
	std::vector<Worker*> &chefs;
	std::vector<Worker*> &carpenters;
	std::vector<Worker*> &armers;
	ProtectedQueue &q_wheat;
	ProtectedQueue &q_wood;
	ProtectedQueue &q_ca_ir;
	ProtectedInventory &inv;
	ProtectedPoints &points;
	/*
		Se encarga de llenar las distintas colas de trabajadores, reservando
		memoria en el heap para cada trabajador, el usuario debe hacerse cargo
		de liberarla, llamando a destroyWorkers().
		Lanza "WorkerCountException" en caso de que count sea < 0.
		Lanza "UnknownWorkerException" en caso de el archivo contenga un tipo
		de trabajador desconocido.
	*/
	void createWorkers(const std::string &job, const int amount);
	void startWorkers(std::vector<Worker*> &workers);
	/*
		Se encarga de liberar la memoria pedida por createWorkers(...), y de
		hacer esperar a cada trabajador(finalizado) a que los demás terminen.
	*/
	void destroyWorkers(std::vector<Worker*> &workers);

public:
	WorkerProcessor(std::vector<Worker*> &farmers,
					std::vector<Worker*> &lumberjacks,
					std::vector<Worker*> &miners,
				    std::vector<Worker*> &chefs,
				    std::vector<Worker*> &carpenters,
				    std::vector<Worker*> &armers,
				    ProtectedQueue &q_wheat,
					ProtectedQueue &q_wood,
					ProtectedQueue &q_ca_ir,
					ProtectedInventory &inv,
					ProtectedPoints &points);
	~WorkerProcessor();
	
	/*
		Se encarga de procesar línea a línea el archivo de trabajadores,
		delegando la creacion de los trabajadores.
		Lanza "FileNotFoundException" en caso de no encontrar el archivo
		especificado.
	*/
	void process(const char *file_name);
	/*
		Pone todos los trabajadores a correr.
	*/
	void startAll();
	/*
		Llama a destroyWorkers() para cada vector referenciado y se encarga de 
		cerrar el inventario y las colas.
	*/
	void destroyAll();
};


#endif // WORKER_PROCESSOR_H
