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
vector<food> all_foods;
//All warehouses that will be recieving food and food requests
map<string, warehouse> warehouses;
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

//Creates a food item form a string, adds to all_foods
void food_item(string f)
{
	vector<string> words;
	size_t pos = 0;
	string item;
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
	string upc = words[4];
	int shelf_life = atoi(words[8].c_str());
	string name;
	for(int i = 11; i <words.size(); i++)
	{
		name += words[i] + " ";
	}
	food foo(upc, shelf_life, name);
	all_foods.push_back(foo);
}

int main()
{

	food_item("FoodItem - UPC Code: 0353264991  Shelf life: 2  Name: chestnut puree with vanilla");
}



