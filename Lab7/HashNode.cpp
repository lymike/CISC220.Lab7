/*
 * HashNode.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: Michael Ly
 */

#include "HashNode.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

hashNode::hashNode() {
	keyword = "";
	values = NULL;
	valuesSize = 0;
	currSize = 0;

}

hashNode::hashNode(string s) {
	keyword = s;
	valuesSize = 100;
	currSize = 0;
	values = new string[valuesSize];
}

hashNode::hashNode(string s,string v) {
	keyword = s;
	valuesSize = 100;
	currSize = 1;
	values = new string[valuesSize];
	values[0] = v;
}

void hashNode::addValue(string v) {
	values[currSize] = v;
	currSize += 1;
	if(currSize==valuesSize) {
		dblArray();
	}
}

void hashNode::dblArray() {
	string *newValues = new string[valuesSize*2];
	for(int i=0; i<valuesSize; i++) {
		newValues[i] = values[i];
	}
	valuesSize = valuesSize*2;
	values = newValues;
}

string hashNode::getRandValue() {
	if (currSize == 0) {
		return "";
	}
	else {
		return values[rand()%currSize];
	}
}

