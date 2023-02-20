#ifndef PASSWORDCRACK_H
#define PASSWORDCRACK_H

#include "Hashcat.h"
#include <iomanip>

using namespace std;

class PasswordCrack
{
private:
	bool solutionFound;
	Session session;
	string filename;
	Wordlist* list;
	ifstream in;
	ofstream out;
	bool sessionFound;
	bool CheckForSession();
	void UpdateSessionFile();
	string GetSolution();

public:
	PasswordCrack();
	PasswordCrack(string file, int let, int sym);
	~PasswordCrack() { delete list; }
	bool Crack();

};

#endif