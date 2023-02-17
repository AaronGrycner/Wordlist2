#include "Header.h"
#include "PasswordCrack.h"

int main() {
	bool resume{ true };
	int letters{ 12 }, symbols{ 1 };
	string filename{ "words.txt" };
	PasswordCrack* crack;

	resume ? crack = new PasswordCrack() : crack = new PasswordCrack(filename, letters, symbols);

	delete crack;
}