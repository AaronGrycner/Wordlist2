#ifndef COMMANDS_H
#define COMMANDS_H

#include <sstream>
#include "Wordlist.h"

using namespace std;

namespace commands 
{
	static filesystem::path directory{ filesystem::current_path() };
	static filesystem::path fileDirectory{ filesystem::current_path().string() + "\\files"};
	static filesystem::path hashcatDirec{ directory.string() + "\\hashcat-6.2.6" };
	string WPA2(string wordlist, string hc22000);
	string Del(string file);
	string cd(string directory);

};

#endif