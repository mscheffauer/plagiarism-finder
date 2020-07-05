#include "utils.h"

#include <cstdlib>
#include <ostream>
#include <algorithm>
#include <iostream>

using namespace std;


bool is_punct(char32_t ch) { return static_cast<bool> (iswpunct(ch)); }
bool is_digit(char32_t ch) { return static_cast<bool> (iswdigit(ch)); }
bool is_null(char32_t ch) { return (ch ==0); }

char32_t to_lower(char32_t ch) { return static_cast<char32_t> (towlower(ch)); }

string normalize(wstring word) {
	wstring::iterator new_end;

	new_end = remove_if(word.begin(), word.end(), is_punct);
	new_end = remove_if(word.begin(), new_end, is_digit);
	new_end = remove_if(word.begin(), new_end, is_null);

	word.erase(new_end, word.end());

	transform(word.begin(), word.end(), word.begin(), to_lower);

	// your new String
	string str(word.begin(), word.end());

	return str;
}

void check_arguments(int argc, int maxFiles) {

	if (argc < (maxFiles + 1)) {
		cerr << "Usage: IndexGen";
		for (int i = 0; i < maxFiles; i++)
		{
			cerr << " <fileName>";
		}
		cerr << endl;
		exit(1);
	}

}
