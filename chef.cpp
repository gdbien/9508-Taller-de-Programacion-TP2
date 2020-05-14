#include "chef.h"

Chef::Chef(ProtectedInventory &inv, ProtectedPoints &points) :
		   Producer(inv, points) {}

Chef::~Chef() {}

void Chef::run() {
	Producer::produce(2, 0, 1, 0, 5);
}
