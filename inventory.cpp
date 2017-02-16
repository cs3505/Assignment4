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
//The first day
int day = 0;


//Creates a food item from a string, adds to all_foods
void create_food_item(string f)
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


// Performs all actions for a next day. Advances the day counter and throws
// away all expired food. (When a food item's expiration day is reached, it 
// expiresat the start of the day. An item with a shelf life of one day will 
// expire at the start of the day after it arrived.)
void next_day()
{
	day++; // Increase the count of the day.
	
	// Go through each item of each warehouse and remove anything that's expired.
	// Iterator instructions from: http://www.learncpp.com/cpp-tutorial/16-3-stl-iterators-overview/
	map<string, warehouse>::iterator it; // Declare iterator
	it = all_warehouses.begin(); // Assign iterator to the start
	while(it != all_warehouses.end()) // While iterator hasn't reached the end
	{
		cout << it->first << endl;
		it->second.check_expired(day); // Have current warehouse expire its food
		++it; // Advance iterator to next pair
	}
}


//Reads in a text file and populates the warehouses, foods, and requests
void read_file(const char * filename)
{
	ifstream infile(filename);
	string line;
	while (getline(infile, line))
	{
		// Find first word from line
		size_t pos = line.find(" ");
		string first_word = line.substr(0, pos);
		// cout << line << endl; // prints out entire line
		// cout << first_word << endl; // prints out first word from line 

		
    	// If first_word is "FoodItem"
		if(first_word.compare("FoodItem") == 0)
		{
			create_food_item(line);
			continue;
		}
		
		// If first first_word is "Warehouse"
		if(first_word.compare("Warehouse") == 0)
		{
			create_warehouse(line);
			continue;
		}
		
		// If first_word is "Receive:"
		if(first_word.compare("Receive:") == 0)
		{
			recieve(line);
			continue;
		}
		
		// If first_word is "Request:"
		if(first_word.compare("Request:") == 0)
		{
			request(line);
			continue;
		}
		
		// If first_word is "Next"
		if(first_word.compare("Next") == 0)
		{
			next_day();
		}
		
		// If first_word is "End", stop modifying inventories
		if(first_word.compare("End") == 0)
			return;
		
	}
}


// Prints out the state of the inventories in their current state.
void print_result()
{
	// Print out "report by" statement
	cout << "Report by Doug Garding and Connor Ottenbacher" << endl;

	// Which products are empty everywhere.
	cout << endl;
	cout << "Unstocked Products:" << endl;
	
	
	// Which products exist in 2 or more warehouses.
	cout << endl;
	cout << "Well-Stocked Products:" << endl;
		
	// Top 3 most popular products.
	cout << endl;
	cout << "Most Popular Products:" << endl;
}


int main()
{
	// Reads in the file and processes its data
	read_file("data1.txt");
	
	
	
	
	create_food_item("FoodItem - UPC Code: 0353264991  Shelf life: 2  Name: chestnut puree with vanilla");
	create_food_item("FoodItem - UPC Code: 0984523912  Shelf life: 1  Name: the orange box");
	
	create_warehouse("Warehouse - Columbus");
	create_warehouse("Warehouse - Seattle");
	create_warehouse("Warehouse - Scottsdale");
	create_warehouse("Warehouse - Tacoma");
	
	recieve("Receive: 0984523912 7 Tacoma");
	
	const food& test_food = all_warehouses["Tacoma"].get_food("0984523912");
	cout << "Name: " << test_food.name << endl;
	cout << "Shelf Life: " << test_food.shelf_life << endl;
	cout << "Total food: " << test_food.total << endl;
	
	recieve("Receive: 0984523912 12 Tacoma");
	recieve("Receive: 0353264991 6 Tacoma");
	recieve("Receive: 0353264991 2 Scottsdale");

	request("Request: 0984523912 5 Tacoma");

	//food dude = all_warehouses["Tacoma"].get_food("0984523912");
	//int s = dude.total;
	
	
	// Prints report on processed data
	print_result();
	return 0;
}



