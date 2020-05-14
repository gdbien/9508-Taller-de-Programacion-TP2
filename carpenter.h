#ifndef CARPENTER_H
#define CARPENTER_H

#include "producer.h"

class Carpenter : public Producer {
public:
	Carpenter(ProtectedInventory &inv, ProtectedPoints &points);
	~Carpenter();
	void run() override;
};

#endif // CARPENTER_H
