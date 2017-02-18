/* Authors Connor Ottenbacher and Doug Garding */
/*This class represents a warehouse storing many different food items and food quantities*/
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
	food &this_food = all_food[upc];
	this_food.add(date, count);
}


// Removes the specified amount of food from the warehouse. The oldest food
// is removed first. If there is not enough food to meet the demand, then
// all available food is removed.
void warehouse::food_request(const std::string & upc, const int & count)
{
	all_food[upc].remove(count);
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
			it->second.total -= it->second.expirations[day]; // Adjusts total for the loss of this amount of food
			it->second.expirations.erase(day); // Removes these food from the map
		}
		
		++it;
	}
}

// Adds all known foods to this warehosues list of all_foods
void warehouse::initialize_foods(const std::map<std::string, food> foods) 
{
	all_food = foods;
}

// Returns a set of all the foods in stock at this warehouse
set<string> warehouse::stocked_items()const
{
	set<string> in_stock_items;
	
	// Go through each food item in catalog, and add it to set if it's in stock at this warehouse.
	for (map<string, food>::const_iterator it = all_food.begin(); it != all_food.end(); ++it) 
	{	
		if (it->second.total > 0) 
		{
			in_stock_items.insert(it->second.upc);
		}
	}

	return in_stock_items;
}


// Returns a food object from this warehouse
food warehouse::get_food(const string upc)
{
	return all_food[upc];
}