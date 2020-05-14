#ifndef CHEF_H
#define CHEF_H

#include "producer.h"

class Chef : public Producer {
public:
	Chef(ProtectedInventory &inv, ProtectedPoints &points);
	~Chef();
	void run() override;
};

#endif // CHEF_H
