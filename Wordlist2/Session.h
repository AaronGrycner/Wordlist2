#ifndef SESSION_H
#define SESSION_H

#include <sstream>
#include <vector>

using namespace std;

struct Session {
	int fileCount{}, letters, symbols, x{}, y{}, z{}, sy{};
	bool done{ false };
	string dict;
	void ReadSessionFile(string file) {
		ifstream in(file);
		string temp;

		// xyzsy variables
		getline(in, temp, ',');
		x = stoi(temp);

		getline(in, temp, ',');
		y = stoi(temp);

		getline(in, temp, ',');
		z = stoi(temp);

		getline(in, temp);
		sy = stoi(temp);

		getline(in, temp);
		dict = temp;
		getline(in, temp);
		letters = stoi(temp);
		getline(in, temp);
		symbols = stoi(temp);
		getline(in, temp);
		fileCount = stoi(temp);
		getline(in, temp);
		temp == "true" ? done = true : done = false;
	}
	string Print() {
		stringstream st;

		st << x << "," << y << "," << z << "," << sy << endl
			<< dict << endl
			<< letters << endl
			<< symbols << endl
			<< fileCount << endl
			<< done << endl;

		return st.str();
	}
};

#endif