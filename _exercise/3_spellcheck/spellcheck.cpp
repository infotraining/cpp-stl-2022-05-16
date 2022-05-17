#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <regex>

using namespace std;

vector<std::string> regex_split(const std::string& s, std::string regex_str = R"(\s+)")
{
    std::vector<std::string> words;

    std::regex rgx(regex_str);

    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;

    while (iter != end)
    {
        words.push_back(*iter);
        ++iter;
    }

    return words;
}

int main()
{
    // wczytaj zawartość pliku en.dict ("słownik języka angielskiego")    
    // sprawdź poprawość pisowni następującego zdania:    
    string input_text = "this is an exmple of very badd snetence";
    vector<string> words = regex_split(input_text);

    // TODO
}