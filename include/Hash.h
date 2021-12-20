#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include "Review.h"

using namespace std;

struct hashTable
{
	string app_version;
	int rpt;
};

class Hash {
public:
	Hash(int m, int m_);
	~Hash() {};

	int m1;
	int m2;
	vector<hashTable> table;
	int current_size;

	int h1(int k);
	int h2(int k);
	int h(int int_k, string k);

	bool empty();
	void insert(string k);
	void insertOtherPosition(string k);
	void print();
	int stringToInt(string k);
	static int calcPrime(int min, int max);
	
	void mostPopularReviews(int M);
	void sortTable(vector<hashTable> table);
	void swap(hashTable* a, hashTable* b);
	int repartTab(vector<hashTable> sortedTable, int beg, int end);
};

#endif // HASH_H
