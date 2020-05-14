#ifndef PROTECTED_INVENTORY_H
#define PROTECTED_INVENTORY_H

#include <map>
#include <mutex>
#include <condition_variable>
#include "resource_types.h"

class ClosedInventoryException : public std::exception {
public:
	const char *what() const throw();
};

class ProtectedInventory {
private:
	bool isClosed;
	std::map<Resource_t, size_t> inv;
	std::mutex m;
	std::condition_variable cv;
	bool enoughOf(const Resource_t res, const size_t amount) const;
	bool enoughResources(const size_t amount_wh, const size_t amount_wo,
						 const size_t amount_ca, const size_t amount_ir) const;
public:
	ProtectedInventory();
	~ProtectedInventory();
	void increaseResource(const Resource_t res, const size_t amount);
	void consumeResources(const size_t amount_wh, const size_t amount_wo,
					      const size_t amount_ca, const size_t amount_ir);
	void printLeft(const Resource_t res) const;
	void printResources() const;
	void close();
};

#endif // PROTECTED_INVENTORY_H
