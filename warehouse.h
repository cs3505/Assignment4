#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <string>
#include <map>
#include <set>
#include "food.h"
/*This class represents a warehouse storing many different food items and food quantities*/
class warehouse
{
public:
	warehouse(const std::string &name); //Constructs a warehouse with the specified name
	warehouse();
	void food_request(const std::string & upc, const int & count); //Removes the specified count of food when requested
	void food_recieve(const std::string & upc, const int & date, const int & count); //Adds the count of food when recieved
	void check_expired(const std::string & date); //Checks for all expired food and removes it
	std::set<std::string> stocked_items()const; //Resturns all of the food items upc numbers which are in stock in this warehouse
	void initialize_foods(const std::map<std::string, food> foods); //Starts the warehouse out with all the foods at a count of 0
	food get_food(const std::string upc); //Returns the food item corresponding to the upc
private:
	std::string name; //Name of the warehouse
	std::map<std::string, food> all_food;	//List of possible foods within the warehouse and their quantities

};
#endif