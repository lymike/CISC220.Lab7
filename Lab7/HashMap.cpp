/*
 * HashMap.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: Michael Ly
 */

#include "HashMap.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

bool isPrime(int k); // Helper Function

hashMap::hashMap(bool hash1, bool coll1){
	first = "";
	numKeys = 0;
	mapSize = 29;
	h1 = hash1;
	c1 = coll1;
	collisionct1 = 0;
	collisionct2 = 0;
	map = new hashNode*[mapSize]; // Creating empty map by default
	for (int i=0; i<mapSize; i++) {
		map[i] = NULL;
	}
}

void hashMap::addKeyValue(string k,string v) {
	int index = getIndex(k);
	if (map[index] == NULL) {
		map[index] = new hashNode(k,v);
		numKeys += 1;
	}
	else{
		map[index]->addValue(v);
	}
	if (numKeys >= mapSize*0.7) {
		reHash();
	}
}

int hashMap::getIndex(string k) {
	int index = 0;
	if (h1 == true) {
		index = calcHash(k);
	}
	else {
		index = calcHash2(k);
	}
	if (map[index]==NULL || k==map[index]->keyword) {
		return index;
	}
	else {
		collisionct1 += 1;
		if (c1 == true) {
			return collHash1(index, k);
		}
		else {
			return collHash2(index, k);
		}
	}
}

int hashMap::calcHash(string k) {
	int index, tmp = 0, len = k.length();
	for (int i=0; i<len; i++) {
		tmp += int(k[i]);
	}
	index = tmp%mapSize;
	return index;
}

int hashMap::calcHash2(string k) { // Converting first 3 characters to ASCII values
	int index = 0;
	for (int i=0; i<3; i++) {
		index += pow(29, i)*int(k[i]);
	}
	index = index%mapSize;
	return index;
}

bool isPrime(int k) { // Helper Function
	int divider = 2;
	bool is_prime = true;
	while (divider < k && k%divider==0) {
		is_prime = false;
		divider++;
	}
	if (k == 1)
		is_prime = false;
	return is_prime;
}

void hashMap::getClosestPrime() {
	int DoubleSize = mapSize*2, lp = 0, rp = 0;
	for (int i=DoubleSize-1; lp==0; i--) {
		if (isPrime(i) == true) {
			lp = i;
		}
	}
	for (int j=DoubleSize+1; rp==0; j++) {
		if (isPrime(j) == true) {
			rp = j;
		}
	}
	int range1 = DoubleSize-lp, range2 = rp-DoubleSize;
	if (range1 < range2) {
		mapSize = lp;
	}
	else {
		mapSize = rp;
	}
}

void hashMap::reHash() {
	int oriSize = mapSize, newIndex;
	getClosestPrime();
	hashNode** oldMap = map;
	map = new hashNode*[mapSize];
	for (int i=0; i<mapSize; i++) { // Emptying original map
		map[i] = NULL;
	}
	for (int i=0; i<oriSize; i++) {
		if (oldMap[i] != NULL) {
			newIndex = getIndex(oldMap[i]->keyword);
			map[newIndex] = oldMap[i];
		}
	}
}

int hashMap::collHash1(int h,string k) { // Linear Probing
	int i = h;
	while (map[i] != NULL) {
		if (k == map[i]->keyword) {
			break;
		}
		else {
			collisionct2 += 1;
			if (i != mapSize-1) {
				i += 1;
			}
			else {
				i = 0;
			}
		}
	}
	return i;
}

int hashMap::collHash2(int h,string k) {	// Quadratic Probing
	int i = h, t = 0;
	while (map[i] != NULL) {
		if (k == map[i]->keyword) {
			break;
		}
		else {
			collisionct2 += 1;
			t++;
			i = (h+(t*t))%mapSize;
		}
	}
	return i;
}

int hashMap::findKey(string k) {
	for(int i=0; i<mapSize; i++) {
		if(k == map[i]->keyword) {
			return i;
		}
	}
	return -1;
}

void hashMap::printMap() {
	cout << "first = " << first << endl;
	cout << "numKeys = " << numKeys << endl;
	cout << "mapSize = " << mapSize << endl;
	cout << "h1 = " << h1 << endl;
	cout << "c1 = " << c1 << endl;
	cout << "collisionct1 = " << collisionct1 << endl;
	cout << "collisionct2 = " << collisionct2 << endl;
}
