#include "food.h"
#include "warehouse.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;

//A list of all foods that the warehouse could possibly contain
map<string, food> all_foods;
//All warehouses that will be recieving food and food requests
map<string, warehouse> all_warehouses;
//Tracks the number of requests recieved for certain food items
map<string, int> requests;
void food_item(string food);
//The first day
int day = 0;

//Reads in a text file and populates the warehouses, foods, and requests
void read_file(const char * filename)
{
	ifstream infile(filename);
	string line;
	while (getline(infile, line))
	{
    	cout << line;
    	cout << endl;
	}
}

//Creates a food item from a string, adds to all_foods
void food_item(string f)
{
	vector<string> words;
	size_t pos = 0;
	string item;
	//Parses the string adding each part to the words vector
	while(f.find(" ") != string::npos)
	{
		pos = f.find(" ");
		item = f.substr(0, pos);
		//cout << item;
		//cout << endl;
		words.push_back(item);
		f.erase(0, pos+1);
	}
	words.push_back(f);
	//Grabs the needed information from the words vector to create a food item
	string upc = words[4];
	int shelf_life = atoi(words[8].c_str());
	string name;
	for(int i = 11; i <words.size(); i++)
	{
		name += words[i];
		if (i < words.size()-1)
			name += " ";
	}
	//Creates the food and adds it to the list of all foods
	food foo(upc, shelf_life, name);
	all_foods.insert(std::pair<string, food>(upc, foo));
}

//Creates a warehouse from a string, and starts it out with all of the foods with a count of 0
void create_warehouse(string w)
{
	size_t pos = 0;
	string item;

	pos = w.find(" - ");
	item = w.substr(pos+3, w.size());

	warehouse wh(item);
	wh.initialize_foods(all_foods);
	all_warehouses.insert(std::pair<string, warehouse>(item, wh));
}

// Performs a recieve operation
void recieve(string rec)
{
	vector<string> words;
	size_t pos = 0;
	string item;
	//Parses the recieve information 
	while(rec.find(" ") != string::npos)
	{
		pos = rec.find(" ");
		item = rec.substr(0, pos);
		words.push_back(item);
		rec.erase(0, pos+1);
	}
	words.push_back(rec);

	string name;
	for(int i = 3; i <words.size(); i++)
	{
		name += words[i];
		if (i < words.size()-1)
			name += " ";
	}
	//Sends the correct recieve command to the appropriate warehouse
	string upc = words[1];
	int quantity = atoi(words[2].c_str());
	warehouse wh = all_warehouses[name];
	wh.food_recieve(upc, day, quantity);
}

int main()
{

	food_item("FoodItem - UPC Code: 0353264991  Shelf life: 2  Name: chestnut puree with vanilla");
	food_item("FoodItem - UPC Code: 0984523912  Shelf life: 1  Name: the orange box");
	create_warehouse("Warehouse - Seattle");
	recieve("Receive: 0353264991 7 Seattle");
}



