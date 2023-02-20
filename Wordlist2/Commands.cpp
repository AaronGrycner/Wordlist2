#include "Commands.h"

using namespace commands;

// takes a filename of a wordlist and .hc22000 as input, executes command to crack
string commands::WPA2(string wordlist, string hc22000)
{
	stringstream st;
	st << "hashcat -m 22000 " << fileDirectory.string() << hc22000 << " " << fileDirectory.string() << wordlist << " -o " << fileDirectory.string() << SOLUTION_FILE << endl;
	return st.str();
}

string commands::Del(string file)
{
	stringstream st;
	st << "del " << file << endl;
	return st.str();
}

string commands::cd(string directory)
{
	stringstream st;
	st << "cd " << directory << endl ;
	return st.str();
}