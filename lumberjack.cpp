#include "lumberjack.h"

Lumberjack::Lumberjack(ProtectedInventory &inv, ProtectedQueue &queue) :
			   Gatherer(inv, queue) {}
			   
Lumberjack::~Lumberjack() {}

void Lumberjack::run() {
	Gatherer::run();
}
