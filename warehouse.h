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
	warehouse(std::string name); //Constructs a warehouse with the specified name
	void food_request(std::string upc, int count); //Removes the specified count of food when requested
	void food_recieve(std::string upc, std::string date, int count); //Adds the count of food when recieved
	void check_expired(std::string date); //Checks for all expired food and removes it
	std::set<std::string> stocked_items()const; //Resturns all of the food items upc numbers which are in stock in this warehouse
private:
	std::string name; //Name of the warehouse
	std::map<std::string, food> all_food;	//List of possible foods within the warehouse and their quantities

};
#endif