#ifndef PROTECTED_POINTS_H
#define PROTECTED_POINTS_H

#include <mutex>

class ProtectedPoints {
private:
	size_t points;
	std::mutex m;
public:
	ProtectedPoints();
	~ProtectedPoints();
	void increasePoints(const size_t amount);
	void printTotal() const;
};

#endif // PROTECTED_POINTS_H
