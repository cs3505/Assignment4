#ifndef FOOD_H
#define FOOD_H
#include <string>
#include <map>
#include <queue>
/*This class represents quantities of a food item stored in a warehouse. The total is stored along with different quantities that expire on certain days. */
class food
{
friend class inventory;
public:
	void add(std::string date, int count);	//Adds to this food total the count, and maps the date and count into the expirations map
	void remove(int count); //Removes the specified count of food items from the expirations, dates, and total
private:
	std::string upc;	//Unique upc code for this food
	int shelf_life;	//Shelf life in days of this food
	std::string name;	//Name of this food item
	std::map<std::string, int> expirations;	//Maps expirations dates to the quantity of food that will expire on that day	
	int total;	//Total number of this food
	std::queue<std::string> dates; //Stores the latest expiration dates of recently added foods. Will correspond to dates in the expirations map
};
#endif