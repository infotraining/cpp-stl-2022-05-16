#include "person.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

std::vector<Person> get_test_data()
{
    std::vector<Person> container;

    container.emplace_back("Gruszka", 45, 3000.0, Gender::male);
    container.emplace_back("Malinowska", 33, 5500.0, Gender::female);
    container.emplace_back("Brzozowski", 28, 2000.0, Gender::male);
    container.emplace_back("Wierzbowski", 54, 7900.0, Gender::male);
    container.emplace_back("Kowalski", 44, 4300.0, Gender::male);
    container.emplace_back("Kowalewska", 23, 2450.0, Gender::female);
    container.emplace_back("Nowak", 58, 4900.0, Gender::male);
    container.emplace_back("Kowal", 29, 3700.0, Gender::male);
    container.emplace_back("Zawadzka", 64, 5300.0, Gender::female);
    container.emplace_back("Hoffander", 53, 7600.0, Gender::male);
    container.emplace_back("Paluch", 53, 2000.0, Gender::male);
    container.emplace_back("Pruski", 41, 9000.0, Gender::male);

    return container;
};

int main()
{
    vector<Person> employees = get_test_data();

    cout << "\n---------------------------------------\n";
    cout << "All employees:\n";
    copy(employees.begin(), employees.end(), ostream_iterator<Person>(cout, "\n"));

    // print employees with salary higher than 3000
    cout << "\n---------------------------------------\n";
    cout << "Employees with salary higher than 3000:\n";

    // print employees with age below 30
    cout << "\n---------------------------------------\n";
    cout << "Employees with age below 30:\n";

    // sort descending by name and print
    cout << "\n---------------------------------------\n";
    cout << "Employees sorted by name (descending):\n";

    // print all women
    cout << "\n---------------------------------------\n";
    cout << "Women:\n";

    // print the 5 youngest employees (in ascending order)
    cout << "\n---------------------------------------\n";
    cout << "The 5 youngest employees:\n";

    // print number of people with salary above average
    cout << "\n---------------------------------------\n";
    cout << "Number of people with salary above average:\n";
}
