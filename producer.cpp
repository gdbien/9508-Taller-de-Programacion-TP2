#include "producer.h"
#include <unistd.h>

#define WORK_TIME 60000

Producer::Producer(ProtectedInventory &inv, ProtectedPoints &points) :
				   Worker(inv, WORK_TIME), points(points) {}

Producer::~Producer() {}

void Producer::produce(const size_t amount_wh, const size_t amount_wo,
					   const size_t amount_ca, const size_t amount_ir,
					   const size_t p_increase) {
	while (true) {
		try {
			inv.consumeResources(amount_wh, amount_wo, amount_ca, amount_ir);
			usleep(WORK_TIME);
			points.increasePoints(p_increase);
		} catch(...) {
			//std::cerr << "Exception: " << e.what() << std::endl;
			break;
		}	
	}
}
