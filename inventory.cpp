#include "food.h"
#include "warehouse.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//A list of all foods that the warehouse could possibly contain
vector<food> all_foods;
//All warehouses that will be recieving food and food requests
map<string, warehouse> warehouses;
//Tracks the number of requests recieved for certain food items
map<string, int> requests;
void food_item(string food);

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

//Creates a food item form a string, adds to all_foods
void food_item(string food)
{
	vector<string> words;
	size_t pos = 0;
	string item;
	cout << food;
	cout << endl;
	while(pos = food.find(":") != string::npos)
	{
		cout << food.find(":");
		item = food.substr(0, pos);
		cout << endl;
		words.push_back(item);
		food.erase(0, pos+1);
	}
	for(int i = 0; i < words.size(); i++)
	{
		cout << words.at(i);
		cout << endl;
	}
}

int main()
{

	food_item("FoodItem - UPC Code: 0353264991  Shelf life: 2  Name: chestnut puree with vanilla");
}



