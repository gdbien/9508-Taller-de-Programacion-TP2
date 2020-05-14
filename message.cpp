#include "message.h"
#include <iostream>

Message::Message() {}

Message::~Message() {}

void Message::print(const ProtectedInventory &inv,
					const ProtectedPoints &points) {
	inv.printResources();
	std::cout << std::endl;
	points.printTotal();
}
