#include "Wordlist.h"

void Wordlist::GetIterLocation(int& x, int& y, int& z, int& sy)
{
	x = xIter - wordVec.begin();
	y = yIter - xIter->begin();
	z = zIter - wordVec[zCalc()].begin();
	sy = symIter - symbolList.begin();
}

Wordlist::Wordlist(Session s) : session{&s}
{
	InitVector();
	SetIterators();
	CalcTotals();
}

void Wordlist::CalcTotals()
{
	for (vector<string> vec : wordVec) {
		totalWords += vec.size() * wordVec[zCalc()].size() * 8 * 13;
	}

	totalBytes = totalWords * (session->letters + session->symbols);
}

void Wordlist::InitVector()
{
	ifstream dict{ session->dict };
	string temp;

	wordVec.resize(session->letters - 1);
	
	while (dict.good()) {
		getline(dict, temp);
		if (temp.size() < session->letters)
			wordVec[temp.size() - 1].push_back(temp);
		dict.peek();
	}

	dict.close();
}

void Wordlist::MakeOutVec()
{
	outVec.clear();
	for (int i{}; i < CHUNK_SIZE; ++i) {
		outVec.push_back(*yIter + *zIter + *symIter);
		session->done = MoveIterators();
	}
}

void Wordlist::SetIterators()
{
	xIter = wordVec.begin() + session->x;
	yIter = (*xIter).begin() + session->y;
	zIter = wordVec[zCalc()].begin() + session->z;
	symIter = symbolList.begin() + session->sy;
}

// incremements iterators and returns true when at end of data
bool Wordlist::MoveIterators()
{
	if (*symIter == symbolList.back()) { // if iterator equals last item
		if (*zIter == wordVec[zCalc()].back()) { // if zIter equals last item in vector
			if (*yIter == xIter->back()) { //if next value of y iter is sentinel
				if ((xIter - wordVec.begin()) == wordVec.size() - 1) // if x iter is at last vector
					return true;
				else {
					symIter = symbolList.begin();
					advance(xIter, 1);
					yIter = xIter->begin();
					zIter = wordVec[zCalc()].begin();
					return false;
				}
			}
			else {
				symIter = symbolList.begin();
				advance(yIter, 1);
				zIter = wordVec[zCalc()].begin();
				return false;
			}
		}
		else {
			symIter = symbolList.begin();
			advance(zIter, 1);
			return false;
		}
	}
	else {
		advance(symIter, 1);
		return false;
	}
}

bool Wordlist::WriteNextFile()
{
	ofstream out{ DIRECTORY + to_string(session->fileCount) + ".txt"};

	MakeOutVec();

	for (string word : outVec) {
		out << word << endl;
	}

	out.close();
	return true;
}