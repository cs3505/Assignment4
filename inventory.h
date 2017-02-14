#ifndef INVENTORY_H
#define	INVENTORY_H
#include <string>
#include <map>
#include <vector>
#include "warehouse.h"
#include "food.h"
class inventory
{
	private:
		std::vector<food> all_foods;
		std::map<std::string, warehouse> warehouses;
		std::map<std::string, int> requests;
	public:
		static void read_file(std::string filename);
		inventory();
		
};
#endif