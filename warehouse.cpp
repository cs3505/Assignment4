#include "warehouse.h"
#include "food.h"
#include <string>
#include <iostream>
#include <map>
using namespace std;
//Warehouse constructor
warehouse::warehouse(const string &n)
{
	name = n;
}
warehouse::warehouse()
{

}

void warehouse::food_recieve(const std::string & upc, const int & date, const int & count)
{
	food f = all_food[upc];
	f.add(date, count);
}
void warehouse::initialize_foods(const std::map<std::string, food> & foods)
{
	all_food = foods;
}