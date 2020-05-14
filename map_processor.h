#ifndef MAP_PROCESSOR_H
#define MAP_PROCESSOR_H

#include "protected_queue.h"

class UnknownResourceException : public std::exception {
public:
	const char *what() const throw();
};

class MapProcessor {
private:
	ProtectedQueue &q_wheat;
	ProtectedQueue &q_wood;
	ProtectedQueue &q_ca_ir;
	/*
		Se encarga de llenar la cola con el recurso y cantidad, y realiza el
		close() de la cola, para avisar que se termino de llenar.
	*/
	void fillQueue(ProtectedQueue &p_queue,const Resource_t res,
				   const size_t amount);
	
public:
	MapProcessor(ProtectedQueue &q_wheat,
				 ProtectedQueue &q_wood,
				 ProtectedQueue &q_ca_ir);
	~MapProcessor();
	/*
		Se encarga de procesar línea a línea el mapa del archivo, delegando el
		llenado de las colas.
		Lanza "FileNotFoundException" en caso de no encontrar el archivo
		especificado.
		Lanza "UnknownResourceException" en caso de que se encuentre con un 
		caracter desconocido.
	*/
	void process(const char* file_name);
};

#endif // MAP_PROCESSOR_H
