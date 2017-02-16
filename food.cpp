#include "food.h"
#include <string>
#include <map>
#include <queue>
#include <iostream>

//Creates a new food object with a upc number, shelf life, and name
food::food(std::string &upc, int &shelf_life, std::string &name)
{
	this->upc = upc;
	this->shelf_life = shelf_life;
	this->name = name;
	this->total = 0;
}
food::food()
{

}

//Adds the food to the total and corresponding expirations
void food::add(const int & date, const int & count)
{
	this->total += count;
	//Expiration date calculated from the date that this food was inserted plus its shelf life
	int exp = date + shelf_life;
	//If there is already a quantity of food expiring on the same day, add to the count of that group of food
	if(expirations.count(exp))
	{
		expirations[exp] += count;
	}
	//Otherwise we add the new group of foods to expire on this day, and add its date to the queue
	else
	{
		expirations.insert(std::pair<int, int>(exp, count));
		dates.push(date);
	}
}

// Removes the specified amount of this food
void food::remove(int count)
{
	// If there's no more of this food
	if(expirations.size() == 0)
		return;
	
	// If the amount of the closest date is more than what's needed
	if(dates.front() > count)
	{
		expirations[dates.front()] -= count;
		total -= count;
	}
	
	// If amount of the closest date is equal to what's needed
	if(dates.front() == count)
	{
		expirations.erase(dates.front());
		dates.pop();
		total -= count;
	}
	
	// If amount of the closest date is less than what's needed
	if(dates.front() < count)
	{
		total -= expirations[dates.front()]; // Decrease total
		count -= expirations[dates.front()]; // Decrease count
		expirations.erase(dates.front()); // Erase this group of oldest food
		dates.pop(); // Remove this expiration date
		remove(count); // Recursive call to remove remaining amount.
	}
}



