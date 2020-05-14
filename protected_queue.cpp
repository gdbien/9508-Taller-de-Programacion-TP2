#include "protected_queue.h"

const char* ClosedQueueException:: what() const throw() {
	return "Queue is closed";	
}

ProtectedQueue::ProtectedQueue() : isClosed(false) {}

ProtectedQueue::~ProtectedQueue() {}

void ProtectedQueue::push(const Resource_t res) {
	std::unique_lock<std::mutex> lk(m);
	queue.push(res);
	cv.notify_all();
}

Resource_t ProtectedQueue::pop() {
	std::unique_lock<std::mutex> lk(m);
	while (queue.empty()) {
		if (isClosed) {
			throw ClosedQueueException();
		}
		cv.wait(lk);
	}
	Resource_t res = queue.front();
	queue.pop();
	return res;
}

void ProtectedQueue::close() {
	std::unique_lock<std::mutex> lk(m);
	isClosed = true;
	cv.notify_all();
}
