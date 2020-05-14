#ifndef MINER_H
#define MINER_H

#include "gatherer.h"
#include "protected_inventory.h"
#include "protected_queue.h"

class Miner : public Gatherer {
public:
	Miner(ProtectedInventory &inv, ProtectedQueue &queue);
	~Miner();
	void run();
};

#endif // MINER_H
