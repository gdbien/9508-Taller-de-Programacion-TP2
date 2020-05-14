#include "protected_inventory.h"
#include <iostream>
#include "resource_types.h"

const char* ClosedInventoryException:: what() const throw() {
	return "Inventory is closed";	
}

ProtectedInventory::ProtectedInventory() : isClosed(false) {}

ProtectedInventory::~ProtectedInventory() {}

void ProtectedInventory::increaseResource(const Resource_t res,
									      const size_t amount) {
	std::unique_lock<std::mutex> lk(m);
	inv[res] += amount;
	cv.notify_all();
}

bool ProtectedInventory::enoughOf(const Resource_t res, const size_t amount)
								  const {
	int inv_amount;
	try {
		inv_amount = inv.at(res);
	} catch(std::out_of_range &e) {
		return false;
	}
	inv_amount -= amount;
	return (inv_amount >= 0) ? true : false;
}

bool ProtectedInventory::enoughResources(const size_t amount_wh,
										 const size_t amount_wo, 
										 const size_t amount_ca,
										 const size_t amount_ir) const {
	return enoughOf(WHEAT, amount_wh) && enoughOf(WOOD, amount_wo) &&
		   enoughOf(CARBON, amount_ca) && enoughOf(IRON, amount_ir);
}

void ProtectedInventory::consumeResources(const size_t amount_wh,
										  const size_t amount_wo,
										  const size_t amount_ca,
										  const size_t amount_ir) {
	std::unique_lock<std::mutex> lk(m);
	while (!enoughResources(amount_wh, amount_wo, amount_ca , amount_ir)) {
		if (isClosed) throw ClosedInventoryException();
		cv.wait(lk);	
	}
	inv[WHEAT] -= amount_wh;
	inv[WOOD] -= amount_wo;
	inv[CARBON] -= amount_ca;
	inv[IRON] -= amount_ir;
}


void ProtectedInventory::printLeft(const Resource_t res) const {
	std::cout << "  - " << ResourceTypes::getName(res) << ": " << inv.at(res)
			  << std::endl; 
}

void ProtectedInventory::printResources() const {
	std::cout << "Recursos restantes:" << std::endl;
	printLeft(WHEAT);
	printLeft(WOOD);
	printLeft(CARBON);
	printLeft(IRON);
}

void ProtectedInventory::close() {
	std::unique_lock<std::mutex> lk(m);
	isClosed = true;
	cv.notify_all();
}
