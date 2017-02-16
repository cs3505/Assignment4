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
	cout << f.total;
	cout << endl;
	f.add(date, count);
	cout << f.total;
	cout << endl;
	all_food[upc] = f;
	cout << all_food[upc].total;
	cout << endl;
}

// Removes the specified amount of food from the warehouse. The oldest food
// is removed first. If there is not enough food to meet the demand, then
// all available food is removed.
void warehouse::food_request(const std::string & upc, const int & count)
{
	food f = all_food[upc];
	f.remove(count);
}

void warehouse::initialize_foods(const std::map<std::string, food> foods) 
{
	for (map<string, food>::const_iterator it = foods.begin(); it != foods.end(); it++)
	{
		this->all_food.insert(pair<string, food>(it->first, it->second));
	}
}
food warehouse::get_food(const string upc)
{
	return all_food[upc];
}