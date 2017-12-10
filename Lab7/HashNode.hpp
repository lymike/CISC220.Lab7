/*
 * HashNode.hpp
 *
 *  Created on: Dec 1, 2017
 *      Author: Michael Ly
 */

#ifndef HASHNODE_HPP_
#define HASHNODE_HPP_

#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;

class hashNode {

	friend class hashMap;
	string keyword;
	string* values;
	int valuesSize;
	int currSize;

public:
	hashNode();
	hashNode(string s);
	hashNode(string s, string v);
	void addValue(string v);
	void dblArray();
	string getRandValue();
};



#endif /* HASHNODE_HPP_ */
