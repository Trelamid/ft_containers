#include <iostream>
#include <map>
#include "Map.h"
#include "Vector.h"

//using namespace ft;

int main() {
	/*map<string, int> auf;
    map<string, int>::iterator itAuf;
    auf["raw"] = 1;
    auf["gaw"] = 2;
    auf["caw"] = 3;
    auf["row"] = 4;
    auf["ris"] = 5;
    auf["gaa"] = 6;
    itAuf = auf.begin();
    for (int i = 0; i < auf.size(); i++) {
        cout<<itAuf->second << endl;
    itAuf++;

    ft::map<int, string> my;
    ft::map<int, string> my1 = my;*/

	ft::vector<int> vector;

	vector[0] = 4;

	vector.push_back(5);
	vector.push_back(5);
	vector.push_back(5);
//	vector.at(8);
	vector.pop_back();
//	vector.assign();
//	vector.clear();
//	vector.swap(vector);
	unsigned int a = 3;
	vector.assign(a, 1);
	std::cout << vector << vector.size() << vector.capacity();

}
