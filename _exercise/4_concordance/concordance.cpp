#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <chrono>

using namespace std;

/*
    Napisz program zliczający ilosc wystapien danego slowa w pliku tekstowym. Wyswietl 10 najczęściej występujących slow (w kolejności malejącej).
*/

std::vector<std::string> load_words(std::istream& in)
{
    std::vector<std::string> words;

    std::string word;
    while(in >> word)
    {
        words.push_back(word);
    }

    return words;
}

int main()
{
    std::string word = "Ala";
    assert(boost::to_upper_copy(word) == "ALA");

    const string file_name = "tokens.txt";

    ifstream fin(file_name);

    if (!fin)
        throw runtime_error("File "s + file_name + " can't be opened");


    auto make_concordance = [](const auto& words) {
        std::unordered_map<std::string, int> concordance(20753);
        //std::map<std::string, int> concordance;

        for(const auto& w : words)
            concordance[boost::to_upper_copy(w)]++;

        return concordance;
    };

    auto make_rating = [](const auto& concordance) {
        std::multimap<int, std::string, std::greater<>> rating;

        for(const auto& kv : concordance)
            rating.emplace(kv.second, kv.first);

        return rating;
    };

    auto words = load_words(fin);

    auto t_start = std::chrono::high_resolution_clock::now();

    auto rating = make_rating(make_concordance(words));

    auto t_end = std::chrono::high_resolution_clock::now();

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count() << "ms\n";

    auto it = rating.begin();
    for(int i = 0; i < 10; ++i, ++it)
    {
        std::cout << it->second << " - " << it->first << "\n";
    }
}
