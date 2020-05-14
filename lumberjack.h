#ifndef LUMBERJACK_H
#define LUMBERJACK_H

#include "gatherer.h"
#include "protected_inventory.h"
#include "protected_queue.h"

class Lumberjack : public Gatherer {
public:
	Lumberjack(ProtectedInventory &inv, ProtectedQueue &queue);
	~Lumberjack();
	void run();
};

#endif // LUMBERJACK_H
