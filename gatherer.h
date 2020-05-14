#ifndef GATHERER_H
#define GATHERER_H

#include "worker.h"
#include "protected_inventory.h"
#include "protected_queue.h"

class Gatherer : public Worker {
private:
	ProtectedQueue &queue;
public:
	Gatherer(ProtectedInventory &inv, ProtectedQueue &queue);
	~Gatherer();
	void run() override;
};

#endif // GATHERER_H
