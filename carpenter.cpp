#include "carpenter.h"

Carpenter::Carpenter(ProtectedInventory &inv, ProtectedPoints &points) :
				     Producer(inv, points) {}

Carpenter::~Carpenter() {}

void Carpenter::run() {
	Producer::produce(0, 3, 0, 1, 2);
}
