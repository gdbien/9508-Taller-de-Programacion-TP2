#include "worker.h"

Worker::Worker(ProtectedInventory &inv, size_t work_time) : inv(inv),
			   work_time(work_time) {}

Worker::~Worker() {}
