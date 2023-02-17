#include "PasswordCrack.h"

void PasswordCrack::UpdateSessionFile()
{
	list->GetIterLocation(session.x, session.y, session.z, session.sy); // get iterator data from wordlist and set into variables

	out.open(DIRECTORY + SESSION_FILE, std::ofstream::out | std::ofstream::trunc);

	out << session.Print();

	out.close();
}

PasswordCrack::PasswordCrack() //default constructor for resuming session, automatically checks for session file
{
	if (CheckForSession()) {
		session.ReadSessionFile(DIRECTORY + SESSION_FILE);
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
	Crack();
}

bool PasswordCrack::Crack()
{
	// create folder for word files
	CreateDirectory(LDIRECTORY, NULL);

	cout << setprecision(2) << fixed;

	while (!session.done) {
		list->WriteNextFile();
		++session.fileCount;
		UpdateSessionFile();
		cout << ((session.fileCount * CHUNK_SIZE) / static_cast<double>(list->GetTotalWords())) * 100 << "% done" << endl;
		// crack wrapper will do something here
		
	}

	return false;
}

bool PasswordCrack::CheckForSession()
{
	in.open(DIRECTORY + SESSION_FILE);

	if (!in.good() || in.peek() == EOF) {
		in.close();
		return false;
	}
	else {
		in.close();
		return true;
	}

	
}