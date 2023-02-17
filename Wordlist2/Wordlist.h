#ifndef WORDLIST_H
#define WORDLIST_H

#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include "Session.h"

using namespace std;

const int CHUNK_SIZE{ 10000 };
const string DIRECTORY{ "files\\" }, SESSION_FILE{ "session.txt" };
const LPCWSTR LDIRECTORY{ L"files" };

class Wordlist
{
private:
	vector<vector<string>> wordVec;
	vector<string> outVec;
	string dictName;

	Session* session;

	vector<vector<string>>::iterator xIter; // iterates over vector of vecs
	vector<string>::iterator yIter, zIter; // y iterates over first word, z iterates over vector with appropriately size second word
	vector<char>::iterator symIter; // iterates over symbol list

	vector<char> symbolList{ '!', '@', '#', '$', '%', '&', '?' };
	void InitVector(); // read file into vectors
	void MakeOutVec(); // create vector of next chunk of data
	bool MoveIterators(); // incrementes iterators, returns false if we are at the end of data
	void SetIterators(); // sets the location of the iterators with passed ints
	int zCalc() { return (session->letters - 2) - (xIter - wordVec.begin()); } // calculates the somewhat complicated position of the z iterator's vector in the wordVec vector
	void CalcTotals();
	int totalWords{};
	double totalBytes{};

public:
	Wordlist(Session session); // constructor for resumimg session
	void GetIterLocation(int& x, int& y, int& z, int& sy); // returns the current location of the iterators
	bool WriteNextFile();
	double GetTotalWords() { return totalWords; }

};


#endif