#include "utils.h"

#include <set>
#include <iomanip>
#include <iterator>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

using entry_set_t = map<string, set<int>>;

#define MAX_COMPARES 2

int main(int argc, char* argv[]) {

	ifstream fin[MAX_COMPARES];
	entry_set_t words[MAX_COMPARES];
	int current_line_nr[MAX_COMPARES] = { 0 };

	check_arguments(argc, MAX_COMPARES);

	for (int i = 0; i < MAX_COMPARES; i++)
	{

		fin[i].open(argv[i + 1]);
		cout << "Creating index of file: " << argv[i + 1]  << " ..." << endl;
		if (fin[i].fail()) {
			cerr << "Could not open file: " << argv[i + 1] << endl;
			exit(2);
		}

		string line;
		while (fin[i].good()) {
			current_line_nr[i]++;

			getline(fin[i], line);
			istringstream line_stream(line);

			for_each(istream_iterator<string>(line_stream),
				istream_iterator<string>(),
				// concise lambda
				[&](const string& word) {
				wstring wstr(word.begin(), word.end());
				string temp = normalize(wstr);
				if(temp.length() > 0) {
					words[i][temp].insert(current_line_nr[i]);
				}
				});

		}

		fin[i].close();
	
		for (const auto& entry : words[i]) {
			cout << setw(15) << entry.first << "(" << entry.second.size() << "):";
			cout << endl;
		}

		cout << "count words: " << words[i].size() << endl << endl << endl;

	}

	//make intersection
	entry_set_t intersection;

	set_intersection(words[0].begin(), words[0].end(),
		words[1].begin(), words[1].end(),
		inserter(intersection, intersection.begin()),
		[](pair<string, set<int>> p1, pair<string, set<int>>p2) {
		return p1.first < p2.first;
	}
	);

	//output intersection, calculate numIntersect
	float numIntersect = 0; 

	for (const auto& entry : intersection) {
		numIntersect += wordcountMatch(words[0].at(entry.first).size(), words[1].at(entry.first).size());
	}

	//here calculate intersection plagiate numbers: take higher from two percentages

	float percentageOutput = (min(words[0].size(), words[1].size()) != 0) ? ((numIntersect / min(words[0].size(), words[1].size()))) : (0);
	
	cout << endl << "The two files match with a percentage of: " << (percentageOutput * 100) << " %" << endl;
		
	return 0;

}