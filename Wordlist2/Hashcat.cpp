#include "Hashcat.h"

// takes the name of a batch file as input and executes it, returns success or failure
bool Hashcat::MakeProcess(wstring batchName)
{
	int stat;

	// windows api datatypes for process creation
	wstring t{ filesystem::current_path().wstring() + L"\\files" };
	wstring c{ L"/C " + t + L"\\" + batchName};

	LPWSTR cmd = c.data();

	LPCWSTR app = L"C:\\WINDOWS\\system32\\cmd.exe",
		direc = t.data();

	// startupinfo struct
	STARTUPINFO startup;
	LPSTARTUPINFO si = &startup;

	// process info struct
	PROCESS_INFORMATION process;
	LPPROCESS_INFORMATION pi = &process;

	// allocate memory for structs
	ZeroMemory(&startup, sizeof(startup));
	startup.cb = sizeof(startup);
	ZeroMemory(&process, sizeof(process));

	stat = CreateProcess(
		app,
		cmd,
		NULL,
		NULL,
		false,
		0,
		NULL,
		direc,
		si,
		pi);

	DWORD d = GetLastError();

	return stat;

}

// takes the name and contents of a batch file as input
void Hashcat::MakeBatchFile(string batchName, string cmds)
{
	ofstream out{ commands::fileDirectory.string() + batchName}; // open stream in the files folder with name of .bat file

	// make file
	out << cmds;
	out.close();
}

bool Hashcat::SystemCall(string batchname)
{
	string directory = commands::directory.string() + "\\files";

	system((directory + "\\" + batchname).c_str());

	if (filesystem::is_empty(commands::fileDirectory.string() + SOLUTION_FILE))
		return false;
	else
		return true;
}

// utility to convert a string to LPSTR
LPSTR Hashcat::Str2LPSTR(CHAR* ch, string str)
{
	ch = new CHAR[str.size()];
	str.copy(ch, str.size(), 0);
	LPSTR temp{ ch };
	delete[] ch;

	return temp;
}

bool Hashcat::operator()(const Session& s) 
{ 
	string wordlist = "\\" + to_string(s.fileCount) + ".txt";
	string batch = "\\" + to_string(s.fileCount) + ".bat";
	string cms = 
		commands::cd(commands::hashcatDirec.string()) + 
		commands::WPA2(wordlist, "\\a.hc22000") +
		commands::Del("C:\\Users\\mrzee\\Desktop\\Wordlist2\\Wordlist2\\files" + wordlist) +
		commands::Del("C:\\Users\\mrzee\\Desktop\\Wordlist2\\Wordlist2\\files" + batch);

	MakeBatchFile(batch, cms);
	return SystemCall(batch);
}
