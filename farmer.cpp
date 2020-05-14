#include "farmer.h"

Farmer::Farmer(ProtectedInventory &inv, ProtectedQueue &queue) :
			   Gatherer(inv, queue) {}
			   
Farmer::~Farmer() {}

void Farmer::run() {
	Gatherer::run();
}
