#include <iostream>
#include <vector>
#include <string>
#include "worker.h"
#include "protected_queue.h"
#include "map_processor.h"
#include "worker_processor.h"
#include "protected_points.h"
#include "message.h"

int main(int argc, char const *argv[]) {
	if (argc != 3) {
		std::cerr << "Error: Usage is: ./tp $worker_file.txt "
					 "$map_file.txt" << std::endl;
		return 1;
	}
	std::vector<Worker*> farmers, lumberjacks, miners, carpenters,
						 chefs, armers;
	ProtectedQueue q_wheat, q_wood, q_ca_ir;
	ProtectedInventory inv;
	ProtectedPoints points;
	WorkerProcessor worker_pro(farmers, lumberjacks, miners, chefs, carpenters,
							   armers, q_wheat, q_wood, q_ca_ir, inv, points);
	MapProcessor map_pro(q_wheat, q_wood, q_ca_ir);
	try {
		worker_pro.process(argv[1]);
		worker_pro.startAll();
		map_pro.process(argv[2]);
		worker_pro.destroyAll();
		Message::print(inv, points);
	} catch(const std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		worker_pro.destroyAll();
		return 1;
	}
	return 0;
}
