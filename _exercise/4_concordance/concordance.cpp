#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_map>
#include <set>
#include <string>

using namespace std;

/*
    Napisz program zliczający ilosc wystapien danego slowa w pliku tekstowym. Wyswietl 20 najczęściej występujących slow (w kolejności malejącej).
*/

int main()
{
    const string file_name = "proust.txt";

    ifstream fin(file_name);

    if (!fin)
        throw runtime_error("File "s + file_name + " can't be opened");
}
