#include "map_processor.h"
#include <iostream>
#include <fstream>
#include <string>
#include "letter_counter.h"
#include "resource_types.h"
#include "file_exception.h"

const char* UnknownResourceException:: what() const throw() {
	return "Unknown characters in file";	
}

MapProcessor::MapProcessor(ProtectedQueue &q_wheat,
				 		   ProtectedQueue &q_wood,
				 		   ProtectedQueue &q_ca_ir) :
				           q_wheat(q_wheat), q_wood(q_wood), q_ca_ir(q_ca_ir) {}

MapProcessor::~MapProcessor() {}

void MapProcessor::fillQueue(ProtectedQueue &p_queue, const Resource_t res,
							 const size_t amount) {
	for (size_t i = 0; i < amount; i++) {
		p_queue.push(res);
	}
	p_queue.close();
}

void MapProcessor::process(const char* file_name) {
	std::ifstream input(file_name, std::ifstream::in);
	std::string line;
	size_t wheat_count, wood_count, carbon_count, iron_count, res_count;
	if (!input.is_open()) throw FileNotFoundException();
	while (std::getline(input, line)) {
		wheat_count = LetterCounter::count(line, WHEAT);
		wood_count = LetterCounter::count(line, WOOD);
		iron_count = LetterCounter::count(line, IRON);
		carbon_count = LetterCounter::count(line, CARBON);
		res_count = wheat_count + carbon_count + wood_count + iron_count;
    	if (line.length() != res_count) throw UnknownResourceException();
    	fillQueue(q_wheat, WHEAT, wheat_count);
    	fillQueue(q_wood, WOOD, wood_count);
    	fillQueue(q_ca_ir, CARBON, carbon_count);
    	fillQueue(q_ca_ir, IRON, iron_count);
  	}
}
