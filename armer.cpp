#include "armer.h"
#include <iostream>

Armer::Armer(ProtectedInventory &inv, ProtectedPoints &points) :
			 Producer(inv, points) {}

Armer::~Armer() {}

void Armer::run() {
	Producer::produce(0, 0, 2, 2, 3);
}
