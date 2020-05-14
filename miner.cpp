#include "miner.h"

Miner::Miner(ProtectedInventory &inv, ProtectedQueue &queue) :
			 Gatherer(inv, queue) {}
			   
Miner::~Miner() {}

void Miner::run() {
	Gatherer::run();
}
