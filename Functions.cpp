#include "Functions.h"

bool compareWords(wordObject i, wordObject j) {
	return j.word > i.word;
}

std::string toLowerString(std::string oldString) {
	std::string newString;
	for (int i = 0; i < oldString.length(); i++) {
		newString += tolower(oldString[i]);
	}
	return newString;
}

void readWords(std::vector<wordObject> &words) { //unsorted
	std::ifstream infile("wordlist.txt");
	std::string newWord;
	wordObject tempObject;
	tempObject.count = 1;
	int assigments = 0, comparisons = 0;
	while (infile >> newWord) {
		if (!isalpha(newWord[0])) {
			continue;
		}

		newWord = toLowerString(newWord);

		bool foundWord = false;
		for (int i = 0; i < words.size(); ++i) {
			if (words[i].word == newWord) {
				foundWord = true;
				words[i].count += 1;
				break;
			}
			++comparisons;
		}

		if (!foundWord) {
			tempObject.word = newWord;
			words.push_back(tempObject);
			std::cout << newWord << std::endl;
			++assigments;
		}
	}

	std::cout << "Unique words = " << words.size() << std::endl;
	std::cout << "Linear Comparisons: " << comparisons << " Assigments: " << assigments << std::endl;
	std::sort(words.begin(), words.end(), compareWords);
	for (int i = 0; i < 10; i++) {
		std::cout << words[i].word << ":" << words[i].count << std::endl;
	}
	for (int i = words.size()-10; i < words.size(); i++) {
		std::cout << words[i].word << ":" << words[i].count << std::endl;
	}
	
	infile.close();
}

int binarySearch(std::vector<wordObject> &words, int l, int r, std::string x, int &comparisons)
{
	while (r >= l)
	{
		int mid = l + (r - l) / 2;

		// If the element is present at the middle  
		// itself 
		if (words[mid].word == x)
			return mid;
 
		if (words[mid].word > x)
			r = mid - 1;
		else
			l = mid + 1;

		++comparisons;

	}

	// We reach here when element is not  
	// present in array 
	return l;
}


void binaryReadWords(std::vector<wordObject> &words) {
	std::ifstream infile("wordlist.txt");
	std::string newWord;
	wordObject tempObject;
	tempObject.count = 1;
	int assigments = 0, comparisons = 0;
	while (infile >> newWord) {
		if (!isalpha(newWord[0])) {
			continue;
		}

		newWord = toLowerString(newWord);

		int wordIndex = 0;
		int l = 0;
		int r = words.size()-1;

		
		wordIndex = binarySearch(words, l, r, newWord, comparisons);

		if (wordIndex > words.size() - 1 || words.size() == 0) {
			tempObject.word = newWord;
			words.push_back(tempObject);
			std::cout << newWord << std::endl;
			++assigments;
		} else if (words[wordIndex].word != newWord) {
			tempObject.word = newWord;
			words.insert(words.begin() + wordIndex, tempObject);
			std::cout << newWord << std::endl;
			++assigments;
		}
		else {
			++words[wordIndex].count;
		}
	}

	std::cout << "Unique words = " << words.size() << std::endl;
	std::cout << "Comparisons: " << comparisons << " Assignments: " << assigments << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << words[i].word << ":" << words[i].count << std::endl;
	}
	for (int i = words.size() - 10; i < words.size(); i++) {
		std::cout << words[i].word << ":" << words[i].count << std::endl;
	}

	infile.close();
}

void hashTable(std::vector<wordObject> &words) {
	std::hash<std::string> string_hash;
	std::vector<std::vector<wordObject>> hashTable(10000);
	int first = string_hash("Toast") % 1000;
	std::vector<wordObject> tempVec;

	std::ifstream infile("wordlist.txt");
	std::string newWord;
	wordObject tempObject;
	tempObject.count = 1;
	int hashIndex = 0;
	int assigments = 0, comparisons = 0;
	while (infile >> newWord) {
		if (!isalpha(newWord[0])) {
			continue;
		}

		newWord = toLowerString(newWord);

		bool found = false;
		hashIndex = string_hash(newWord) % 10000;
		tempVec = hashTable[hashIndex];
		for (int i = 0; i < tempVec.size(); i++) {



			if (tempVec[i].word == newWord) {
				++tempVec[i].count;
				hashTable[hashIndex] = tempVec;
				found = true;
				break;
			}
			++comparisons;
		}

		if (!found) {
			tempObject.word = newWord;
			hashTable[hashIndex].push_back(tempObject);
			++assigments;
		}

	}

	std::cout << "Linear Comparisons: " << comparisons << " Assigments: " << assigments << std::endl;

	infile.close();
}
