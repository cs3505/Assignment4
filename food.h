#ifndef FOOD_H
#define FOOD_H
#include <string>
#include <map>
class food
{
	friend class inventory;
	private:
		std::string upc;
		int shelf_life;
		std::string name;
		std::map<std::string, int>;
		int total;

};
#endif