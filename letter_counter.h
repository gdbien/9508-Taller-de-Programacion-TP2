#ifndef LETTER_COUNTER_H
#define LETTER_COUNTER_H

#include <string>

class LetterCounter {
public:
	LetterCounter();
	~LetterCounter();
	static size_t count(const std::string &line, const int letter);
};

#endif // LETTER_COUNTER_H
