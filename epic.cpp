// epic
// Judge Solution
// Ryan Patterson

const char* FILENAME = "epic.in";

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void do_puzzle(istream& in) {
	stringbuf sb;
	in.get(sb);
	// Eat newline following line
	in.get();
	const string& line = sb.str();
	if(line.find("Win") == 0 || line.find("Fail") == 0)
		cout << "Epic ";
	cout << line << endl;
}

int main(int argc, char* argv[]) {
	// ifstream in(FILENAME);
	istream & in = cin;
	int n = 0;
	in >> n;
	// Eat newline following number
	in.get();
	while(n--)
		do_puzzle(in);
	return 0;
}
