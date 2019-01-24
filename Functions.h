#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct wordObject {
	std::string word;
	int count = 0;
};

void readWords(std::vector<wordObject> &words);

void binaryReadWords(std::vector<wordObject> &words);

int binarySearch(std::vector<wordObject> words, int l, int r, std::string x);

std::string toLowerString(std::string oldString);

void hashTable(std::vector<wordObject> &words);

#endif
