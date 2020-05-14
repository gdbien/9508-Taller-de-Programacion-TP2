#include "gatherer.h"
#include <unistd.h>

#define WORK_TIME 50000

Gatherer::Gatherer(ProtectedInventory &inv, ProtectedQueue &queue) :
				   Worker(inv, WORK_TIME), queue(queue) {}
				   
Gatherer::~Gatherer() {}

void Gatherer::run() {
	while (true) {
		try {
			Resource_t res = queue.pop();
			usleep(WORK_TIME);
			inv.increaseResource(res, 1);
		} catch(...) {
			//std::cerr << "Exception: " << e.what() << std::endl;
			break;
		}	
	}	
}
