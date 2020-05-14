#ifndef MESSAGE_H
#define MESSAGE_H

#include "protected_inventory.h"
#include "protected_points.h"

class Message {
public:
	Message();
	~Message();
	static void print(const ProtectedInventory &inv,
				      const ProtectedPoints &points);
};

#endif // MESSAGE_H
