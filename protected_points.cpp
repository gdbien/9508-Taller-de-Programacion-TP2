#include "protected_points.h"
#include <iostream>

ProtectedPoints::ProtectedPoints() : points(0) {}

ProtectedPoints::~ProtectedPoints() {}

void ProtectedPoints::increasePoints(const size_t amount) {
	std::unique_lock<std::mutex> lk(m);
	points += amount;
}

void ProtectedPoints::printTotal() const {
	std::cout << "Puntos de Beneficio acumulados: " << points << std::endl;
}
