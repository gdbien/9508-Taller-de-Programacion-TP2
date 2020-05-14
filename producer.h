#ifndef PRODUCER_H
#define PRODUCER_H

#include "worker.h"
#include "protected_inventory.h"
#include "protected_points.h"

class Producer : public Worker {
private:
	ProtectedPoints &points;
public:
	Producer(ProtectedInventory &inv, ProtectedPoints &points);
	~Producer();
	virtual void run() = 0;
	void produce(const size_t amount_wh, const size_t amount_wo,
			     const size_t amount_ca, const size_t amount_ir,
			     const size_t p_increase);
};

#endif // PRODUCER_H
