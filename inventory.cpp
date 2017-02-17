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

// Forward Declarations of Methods
void read_file(const char * filename);
void create_food_item(string f);
void create_warehouse(string w);
void recieve(string recieve);
void request(string request);
void next_day();
void print_result();
void print_unstocked_products();
void print_well_stocked_products();
void print_popular_products();


/** Main method used as the driver for all of the operations
 ** required to produce the expected results.
 **/
int main()
{
	// Reads in the file and processes its data
	read_file("data3.txt");
	// Prints results at the conclusion of processing the data.
	print_result();
	
	return 0;
}


/** Reads in a text file and populates the warehouses and food items.
 ** Also controls the events for each day as well as moving the 
 ** days forward.
 **/
void read_file(const char * filename)
{
	ifstream infile(filename);
	string line;
	while (getline(infile, line))
	{
		// Find first word from line
		size_t pos = line.find(" ");
		string first_word = line.substr(0, pos);
		
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


/** Creates a food item from a string, and adds it to the list of all foods.
 **/
void create_food_item(string f)
{
	vector<string> words;
	size_t pos = 0;
	string token;
	
	//Parses the string line into tokens, adding each to the vector: 'words'
	while(f.find(" ") != string::npos)
	{
		pos = f.find(" ");
		token = f.substr(0, pos);
		words.push_back(token);
		f.erase(0, pos+1);
	}
	words.push_back(f);
	
	// Separates out the name, UPC, and shelf life from the parsed string line
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


/** Creates a warehouse from a string, and starts it out with 
 ** a catalog of all possible foods, each set with a total of 0.
 **/
void create_warehouse(string w)
{
	// Separate out name of the warehouse
	size_t pos = 0;
	string name;
	pos = w.find(" - ");
	name = w.substr(pos+3, w.size());

	// Construct the warehouse and adds it to the list of all warehouses
	warehouse new_warehouse(name);
	new_warehouse.initialize_foods(all_foods); // Adds all known food to warehouse
	all_warehouses.insert(std::pair<string, warehouse>(name, new_warehouse));
}


/** Performs a recieve operation by telling the appropriate warehouse
 ** how much of a given product it is recieving.
 **/
void recieve(string recieve)
{
	vector<string> words;
	size_t pos = 0;
	string item;
	
	//Parses the string into tokens, adding each to the vector: 'words'
	while(recieve.find(" ") != string::npos)
	{
		pos = recieve.find(" ");
		item = recieve.substr(0, pos);
		words.push_back(item);
		recieve.erase(0, pos+1);
	}
	words.push_back(recieve);

	//Constructs warehouse name after being separated by spaces
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
	warehouse &wh = all_warehouses[name];
	wh.food_recieve(upc, day, quantity);
}


/** Performs a request operation by telling the appropriate warehouse
 ** how much of a given product is being requested. Also increments
 ** the total count for how many times the given product's been requested.
 **/
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

	//Constructs warehouse name after being separated by spaces
	string name;
	for(int i = 3; i <words.size(); i++)
	{
		name += words[i];
		if (i < words.size()-1)
			name += " ";
	}
	
	//Sends the request command to the appropriate warehouse
	string upc = words[1];
	int quantity = atoi(words[2].c_str());
	warehouse &wh = all_warehouses[name];
	wh.food_request(upc, quantity);
	
	// Increases request count for this food.
	requests[upc] += quantity;
}


/** Performs all actions for a next day. Advances the day counter and throws
 ** away all expired food. (When a food item's expiration day is reached, it 
 ** expiresat the start of the day. An item with a shelf life of one day will 
 ** expire at the start of the day after it arrived.)
 **/
void next_day()
{
	day++; // Increase the count of the day.
	
	// Go through each item of each warehouse and remove anything that's expired.
	map<string, warehouse>::iterator it; // Declare iterator
	it = all_warehouses.begin(); // Assign iterator to the start
	while(it != all_warehouses.end()) // While iterator hasn't reached the end
	{
		it->second.check_expired(day); // Have current warehouse expire its food
		++it; // Advance iterator to next pair
	}
}


/** Prints out the final report for the state of the inventories
 ** after all of the daily operations have ben completed.
 **/
void print_result()
{
	// Print out "report by" statement
	cout << "Report by Connor Ottenbacher and Doug Garding" << endl;
	cout << endl;

	// Which products are empty everywhere.
	cout << "Unstocked Products:" << endl;
	print_unstocked_products();
	cout << endl;
	
	// Which products exist in 2 or more warehouses.
	cout << "Well-Stocked Products:" << endl;
	print_well_stocked_products();
	cout << endl;
		
	// Top 3 most popular products.
	cout << "Most Popular Products:" << endl;
	print_popular_products();
	cout << endl;
}


/** Helper method that prints out all of the food items that are 
 ** not in stock in any of the warehouses.
 **/
void print_unstocked_products()
{
	// Get set of all items that we can subtract from
	set<string> out_of_stock_items;
	for (map<string, food>::const_iterator it = all_foods.begin(); it != all_foods.end(); ++it) 
	{		
		out_of_stock_items.insert(it->second.upc);
	}
	
	// Now go through each warehouse to get their lists of in-stock foods
	for (map<string, warehouse>::const_iterator it = all_warehouses.begin(); it != all_warehouses.end(); ++it) 
	{	
		// Get set of current warehouses in-stock items
		set<string> warehouse_items = it->second.stocked_items();
		
		// Remove all of the warehouses items from the out_of_stock_items list.
		for (set<string>::const_iterator it2 = warehouse_items.begin(); it2 != warehouse_items.end(); ++it2) 
		{	
			out_of_stock_items.erase(*it2);
		}
	}
	
	// Now print the items that are out of stock
	for (set<string>::const_iterator it3 = out_of_stock_items.begin(); it3 != out_of_stock_items.end(); ++it3) 
	{	
		cout << *it3 << " " << all_foods[*it3].name << endl;
	}
}


/** Helper method that prints out all of the food items that are 
 ** well stocked. A food item that is well stocked means that at least
 ** one of that item exists in two or more warehouses.
 **/
void print_well_stocked_products()
{
	
}


/** Helper method that prints out the top three most popular products.
 ** If there were less than three different products ever requested, 
 ** then there will only be a print out for as many items were actually
 ** requested. 
 **/
void print_popular_products()
{
	// Loop through the list of all foods 3 times to find 3 top items
	for(int i = 0; i < 3; i++)
	{
		// If there are no more items, we're done.
		// (happens if there were never more than 3 food types requested)
		if(requests.size() < 1)
			break;
		
		int iMost_popular = 0;
		string sMost_popular = "";
		// Optimization loop to find most popular
		for(map<string, int>::iterator it = requests.begin(); it != requests.end(); ++it) // While iterator hasn't reached the end
		{
			// If current food_item is more popular that previous most popular
			if(it->second >= iMost_popular)
			{
				iMost_popular = it->second;
				sMost_popular = it->first;
			}

		}
		requests.erase(sMost_popular);
		
		cout << sMost_popular << " " << all_foods[sMost_popular].name << endl;
	}
}
