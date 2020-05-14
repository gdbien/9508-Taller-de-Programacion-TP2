#include "resource_types.h"
#include <string> //Lo pide cpplint aunque ya este en el header.

ResourceTypes::ResourceTypes() {}

ResourceTypes::~ResourceTypes() {}

std::string ResourceTypes::getName(const Resource_t res) {
	switch(res) {
		case WHEAT:
			return WHEAT_NAME;
		case WOOD:
			return WOOD_NAME;
		case CARBON:
			return CARBON_NAME;
		case IRON:
			return IRON_NAME;
	}
	return NULL;
}  
