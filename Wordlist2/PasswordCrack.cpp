#include "PasswordCrack.h"

void PasswordCrack::UpdateSessionFile()
{
	list->GetIterLocation(session.x, session.y, session.z, session.sy); // get iterator data from wordlist and set into variables

	out.open(FILES_DIRECTORY + SESSION_FILE, std::ofstream::out | std::ofstream::trunc);

	out << session.Print();

	out.close();
}

string PasswordCrack::GetSolution()
{
	ifstream in{ FILES_DIRECTORY + SOLUTION_FILE };
	string temp;

	getline(in, temp);

	return temp;
}

PasswordCrack::PasswordCrack() //default constructor for resuming session, automatically checks for session file
{
	if (CheckForSession()) {
		session.ReadSessionFile(FILES_DIRECTORY + SESSION_FILE);
		list = new Wordlist(session);
		Crack();
	}
	else
		throw runtime_error("No Session File Found!");
}

PasswordCrack::PasswordCrack(string file, int let, int sym)
{
	session.dict = file;
	session.letters = let;
	session.symbols = sym;

	list = new Wordlist(session);
	if (Crack())
		cout << GetSolution();
	else
		cout << "NO SOLUTION";

}

bool PasswordCrack::Crack()
{
	// create folder for word files
	CreateDirectory(LFILES_DIRECTORY, NULL);

	Hashcat hashcat;

	cout << setprecision(2) << fixed;

	while (!session.done) {
		list->WriteNextFile();
		UpdateSessionFile();
		cout << ((session.fileCount * CHUNK_SIZE) / static_cast<double>(list->GetTotalWords())) * 100 << "% done" << endl;
		solutionFound = hashcat(session);
		if (solutionFound) return true;
		++session.fileCount;
		
	}

	return false;
}

bool PasswordCrack::CheckForSession()
{
	in.open(FILES_DIRECTORY + SESSION_FILE);

	if (!in.good() || in.peek() == EOF) {
		in.close();
		return false;
	}
	else {
		in.close();
		return true;
	}
}