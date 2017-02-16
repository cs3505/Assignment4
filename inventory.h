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
		
	public:
		static void read_file(std::string filename);
		inventory();
		
};
#endif