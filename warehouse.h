#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <string>
#include <map>
#include "food.h"
class warehouse
{
	friend class inventory;
	private:
		std::string name;
		std::map<std::string, food> all_food;

};
#endif