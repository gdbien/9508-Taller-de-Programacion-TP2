#ifndef WORKER_H
#define WORKER_H

#include "thread.h"
#include "protected_inventory.h"

class Worker : public Thread {
protected:
	ProtectedInventory &inv;
	size_t work_time;
public:
	Worker(ProtectedInventory &inv, size_t work_time);
	~Worker();
	virtual void run() = 0;
};

#endif // WORKER_H
