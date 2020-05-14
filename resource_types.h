#ifndef RESOURCE_TYPES_H
#define RESOURCE_TYPES_H

#include <string>

#define WHEAT_NAME "Trigo"
#define WOOD_NAME "Madera"
#define CARBON_NAME "Carbon"
#define IRON_NAME "Hierro"

typedef enum {WHEAT ='T', CARBON = 'C', WOOD = 'M', IRON = 'H'} Resource_t;

class ResourceTypes {
public:
	ResourceTypes();
	~ResourceTypes();
	static std::string getName(const Resource_t res);  
};

#endif // RESOURCE_TYPES_H
