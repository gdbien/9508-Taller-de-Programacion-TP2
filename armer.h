#ifndef ARMER_H
#define ARMER_H

#include "producer.h"

class Armer : public Producer {
public:
	Armer(ProtectedInventory &inv, ProtectedPoints &points);
	~Armer();
	void run() override;
};

#endif // ARMER_H
