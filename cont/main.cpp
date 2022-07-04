#include <iostream>
#include "Tree.hpp"
#include "Map.h"
#include <map>

int main() {

	std::map<int, int> map;
	ft::map<int, int> myMap;

	myMap.insert(std::make_pair(1,1));
	myMap.insert(std::make_pair(2,1));
	myMap.insert(std::make_pair(3,1));

	ft::Tree<int, int>::iterator it;
	it = myMap.begin();
	myMap.erase(1);
	myMap.erase(2);
	myMap.erase(3);
//	it = myMap.end();
//	++it;
//	++it;
	std::cout << (*it).first;

//	ft::Node<int, int> auf;
//	auf.key = 1;
//	auf.value = 2;
//
//	ft::Tree<int, int> tree;
//	for (int i = 0; i < 6; i++) {
//		tree.insert(-i-1, 2);
//		tree.insert(i, 2);
//	}

//	tree.insert(0, 1);
//	tree.insert(-1, 2);
//	tree.insert(1, 4);
//	tree.insert(-2, 3);
//	tree.insert(2, 4);
//	tree.insert(-3, 3);
//	tree.insert(3, 4);
//
//	tree.erase(2);
//	tree.erase(0);
//	tree.erase(-1);
//	tree.erase(-3);
//	tree.erase(-2);
//	tree.erase(3);
//	tree.erase(1);
//	tree.erase(3);

//	std::pair<int, int> pair(0,2);
//	map.insert(std::make_pair(0, 1));
//	map.insert(std::make_pair(-1, 2));
//	map.insert(std::make_pair(-2, 3));
//	map.insert(std::make_pair(1, 4));

//	tree.print();

//	std::cout << "\n"<<map.begin()->first << map.end()->first;
}
