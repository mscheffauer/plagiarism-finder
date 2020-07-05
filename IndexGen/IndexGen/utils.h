#pragma once

#include <string>
#include <fstream>

bool is_punct(char32_t ch); 
bool is_digit(char32_t ch); 


char32_t to_lower(char32_t ch);

std::string normalize(std::wstring word);
void check_arguments(int argc, int maxFiles) ;
float inline wordcountMatch(int cnt1, int cnt2) { return ((cnt1 < cnt2) ? ((float)cnt1 / (float)cnt2) : ((float)cnt2 / (float)cnt1)); };
