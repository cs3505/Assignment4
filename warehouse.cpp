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
	all_food.erase(upc);
	all_food.insert(pair<string, food>(upc, f));
	cout << f.total;
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

void warehouse::check_expired(const int day)
{
	// Go through each food item and remove anything that's expired.
	map<string, food>::iterator it; 
	it = all_food.begin(); 
	while(it != all_food.end()) 
	{
		
		// If some of this food expires today
		if (it->second.dates.front() == day) 
		{
			it->second.dates.pop(); // Remove today's date from the queue
			it->second.expirations.erase(day); // Removes these food from the map
		}
		
		++it;
	}
}

// Adds all known foods to this warehosues list of all_foods
void warehouse::initialize_foods(const std::map<std::string, food> foods) 
{
	for (map<string, food>::const_iterator it = foods.begin(); it != foods.end(); it++)
	{
		this->all_food.insert(pair<string, food>(it->first, it->second));
	}
}


// Returns a food object from this warehouse
food warehouse::get_food(const string upc)
{
	return all_food[upc];
}