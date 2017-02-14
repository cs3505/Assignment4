//Tests the warehouse program
#include <iostream>
#include "inventory.h"
using namespace std;
int main()
{
	inventory i;
	cout <<i.read_file("data1.txt");
	cout << endl;
	return 0;
}