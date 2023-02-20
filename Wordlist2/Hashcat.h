#ifndef HASHCAT_H
#define HASHCAT_H

#include "Wordlist.h"
#include <windows.h>

class Hashcat
{
private:
	void MakeBatchFile(string batchName, string cmds);
	bool MakeProcess(wstring batchName); 
	bool SystemCall(string batchname);
	LPSTR Str2LPSTR(CHAR* ch, string str);

public:
	bool operator()(const Session& s);
};

#endif