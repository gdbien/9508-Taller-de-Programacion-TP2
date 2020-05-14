#include "worker_processor.h"
#include <string> //Lo pide cpplint aunque ya este en el header.
#include <vector> //Lo pide cpplint aunque ya este en el header.
#include <iostream>
#include <fstream>
#include "file_exception.h"
#include "farmer.h"
#include "lumberjack.h"
#include "miner.h"
#include "chef.h"
#include "carpenter.h"
#include "armer.h"

#define FARMERS "Agricultores"
#define LUMBERJACKS "Leniadores"
#define MINERS "Mineros"
#define CHEFS "Cocineros"
#define CARPENTERS "Carpinteros"
#define ARMERS "Armeros"

const char* UnknownWorkerException::what() const throw(){
	return "Unknown worker";
}

const char* WorkerCountException::what() const throw(){
	return "Worker count";
}

WorkerProcessor::WorkerProcessor(std::vector<Worker*> &farmers,
								 std::vector<Worker*> &lumberjacks,
								 std::vector<Worker*> &miners,
				    			 std::vector<Worker*> &chefs,
				    			 std::vector<Worker*> &carpenters,
				    			 std::vector<Worker*> &armers,
								 ProtectedQueue &q_wheat,
								 ProtectedQueue &q_wood, 
								 ProtectedQueue &q_ca_ir,
								 ProtectedInventory &inv,
								 ProtectedPoints &points) :
	farmers(farmers), lumberjacks(lumberjacks), miners(miners), chefs(chefs),
	carpenters(carpenters), armers(armers), q_wheat(q_wheat), q_wood(q_wood),
	q_ca_ir(q_ca_ir), inv(inv), points(points) {}


WorkerProcessor::~WorkerProcessor() {}

void WorkerProcessor::createWorkers(const std::string &type, const int amount) {
	if (amount < 0) throw WorkerCountException();
	if (type.compare(FARMERS) == 0) {
		for (int i = 0; i < amount; i++) {
			farmers.push_back(new Farmer(inv, q_wheat));	
		}
	} else if (type.compare(LUMBERJACKS) == 0) {
		for (int i = 0; i < amount; i++) {
			lumberjacks.push_back(new Lumberjack(inv, q_wood));	
		}
	} else if (type.compare(MINERS) == 0) {
		for (int i = 0; i < amount; i++) {
			miners.push_back(new Miner(inv, q_ca_ir));	
		}
	} else if (type.compare(CHEFS) == 0) {
		for (int i = 0; i < amount; i++) {
			chefs.push_back(new Chef(inv, points));	
		}
	} else if (type.compare(CARPENTERS) == 0) {
		for (int i = 0; i < amount; i++) {
			carpenters.push_back(new Carpenter(inv, points));	
		}
	} else if (type.compare(ARMERS) == 0) {
		for (int i = 0; i < amount; i++) {
			armers.push_back(new Armer(inv, points));	
		}
	} else {
		throw UnknownWorkerException();	
	}
}

void WorkerProcessor::startWorkers(std::vector<Worker*> &workers) {
    for (size_t i = 0; i < workers.size(); i++) {
        workers[i]->start();
    }
}

void WorkerProcessor::destroyWorkers(std::vector<Worker*> &workers) {
	for (size_t i = 0; i < workers.size(); i++) {
        workers[i]->join();
        delete workers[i];
    }
}

void WorkerProcessor::process(const char *file_name) {
	std::ifstream input(file_name,std::ifstream::in);
	std::string worker;
	std::string count;
	if (!input.is_open()) throw FileNotFoundException();
	while (std::getline(input, worker, '=') && getline(input, count)) {
		WorkerProcessor::createWorkers(worker, std::stoi(count));
  	}
}

void WorkerProcessor::startAll() {
	startWorkers(chefs);
  	startWorkers(carpenters);
  	startWorkers(armers);
  	startWorkers(farmers);
  	startWorkers(lumberjacks);
  	startWorkers(miners);
}

void WorkerProcessor::destroyAll() {
	q_wheat.close();
	q_wood.close();
	q_ca_ir.close();
	destroyWorkers(farmers);
	destroyWorkers(lumberjacks);
	destroyWorkers(miners);
	inv.close();
	destroyWorkers(chefs);
	destroyWorkers(carpenters);
	destroyWorkers(armers);
}
