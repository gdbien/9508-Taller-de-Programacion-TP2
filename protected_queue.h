#ifndef PROTECTED_QUEUE_H
#define PROTECTED_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include "thread.h"
#include "resource_types.h"

class ClosedQueueException : public std::exception {
public:
	const char *what() const throw();
};

class ProtectedQueue {
private:
	bool isClosed;
	std::mutex m;
	std::queue<Resource_t> queue;
	std::condition_variable cv;
public:
	ProtectedQueue();
	~ProtectedQueue();	
	void push(const Resource_t res);
	Resource_t pop();	
	void close();
};

#endif // PROTECTED_QUEUE_H
