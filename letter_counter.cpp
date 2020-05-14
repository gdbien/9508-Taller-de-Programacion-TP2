#include "letter_counter.h"
#include <string> //Lo pide cpplint aunque ya este en el header.

LetterCounter::LetterCounter() {}

LetterCounter::~LetterCounter() {}

size_t LetterCounter::count(const std::string &line, const int letter) {
	size_t counter = 0;
	size_t line_length = line.length();
	for (size_t i = 0; i < line_length; i++) {
		if (line[i] == letter) counter++;
	}
	return counter;
}
