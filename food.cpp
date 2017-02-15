#include "food.h"
#include <string>
#include <map>
#include <queue>

//Creates a new food object with a upc number, shelf life, and name
food::food(std::string upc, int shelf_life, std::string name)
{
	this->upc = upc;
	this->shelf_life = shelf_life;
	this->name = name;
}