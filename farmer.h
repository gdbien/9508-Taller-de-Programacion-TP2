#ifndef FARMER_H
#define FARMER_H

#include "gatherer.h"
#include "protected_inventory.h"
#include "protected_queue.h"

class Farmer : public Gatherer {
public:
	Farmer(ProtectedInventory &inv, ProtectedQueue &queue);
	~Farmer();
	void run();
};

#endif // FARMER_H
