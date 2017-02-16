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

// Adds the recieved food to the warehouse.
void warehouse::food_recieve(const std::string & upc, const int & date, const int & count)
{
	food f = all_food[upc];
	f.add(date, count);
}

// Removes the specified amount of food from the warehouse. The oldest food
// is removed first. If there is not enough food to meet the demand, then
// all available food is removed.
void warehouse::food_request(const std::string & upc, const int & count)
{
	food f = all_food[upc];
	f.remove(count);
}

void warehouse::initialize_foods(const std::map<std::string, food> & foods) 
{
	all_food = foods;
}