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
	string token;
	
	//Parses the string into tokens, adding each to the vector: 'words'
	while(f.find(" ") != string::npos)
	{
		pos = f.find(" ");
		token = f.substr(0, pos);
		//cout << token << endl;
		words.push_back(token);
		f.erase(0, pos+1);
	}
	words.push_back(f);
	
	//Grabs the needed information from the words vector to create a food item
	string upc = words[4];
	int shelf_life = atoi(words[8].c_str());
	string name;
	//Constructs food item's name after being separated by spaces
	for(int i = 11; i <words.size(); i++)
	{
		name += words[i];
		if (i < words.size()-1)
			name += " ";
	}
	
	//Creates the food and adds it to the list of all foods
	food food_item(upc, shelf_life, name);
	all_foods.insert(std::pair<string, food>(upc, food_item));
}


//Creates a warehouse from a string, and starts it out with all of the foods with a count of 0
void create_warehouse(string w)
{
	// Separate out name of the warehouse
	size_t pos = 0;
	string item;
	pos = w.find(" - ");
	item = w.substr(pos+3, w.size());

	// Construct the warehouse and adds it to the list of all warehouses
	warehouse new_warehouse(item);
	new_warehouse.initialize_foods(all_foods); // Adds all known food to warehouse
	all_warehouses.insert(std::pair<string, warehouse>(item, new_warehouse));
}


// Performs a recieve operation
void recieve(string rec)
{
	vector<string> words;
	size_t pos = 0;
	string item;
	
	//Parses the string into tokens, adding each to the vector: 'words'
	while(rec.find(" ") != string::npos)
	{
		pos = rec.find(" ");
		item = rec.substr(0, pos);
		words.push_back(item);
		rec.erase(0, pos+1);
	}
	words.push_back(rec);

	string name;
	//Constructs warehouse name after being separated by spaces
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


// Handles a request operation
void request(string request)
{
	vector<string> words;
	size_t pos = 0;
	string item;
	
	//Parses the string into tokens, adding each to the vector: 'words'
	while(request.find(" ") != string::npos)
	{
		pos = request.find(" ");
		item = request.substr(0, pos);
		words.push_back(item);
		request.erase(0, pos+1);
	}
	words.push_back(request);

	string name;
	//Constructs warehouse name after being separated by spaces
	for(int i = 3; i <words.size(); i++)
	{
		name += words[i];
		if (i < words.size()-1)
			name += " ";
	}
	
	//Sends the request command to the appropriate warehouse
	string upc = words[1];
	int quantity = atoi(words[2].c_str());
	warehouse wh = all_warehouses[name];
	wh.food_request(upc, quantity);
}





int main()
{
	food_item("FoodItem - UPC Code: 0353264991  Shelf life: 2  Name: chestnut puree with vanilla");
	food_item("FoodItem - UPC Code: 0984523912  Shelf life: 1  Name: the orange box");
	
	create_warehouse("Warehouse - Columbus");
	create_warehouse("Warehouse - Seattle");
	create_warehouse("Warehouse - Scottsdale");
	create_warehouse("Warehouse - Tacoma");
	
	recieve("Receive: 0984523912 7 Tacoma");
	recieve("Receive: 0353264991 6 Tacoma");
	recieve("Receive: 0353264991 2 Scottsdale");
}



