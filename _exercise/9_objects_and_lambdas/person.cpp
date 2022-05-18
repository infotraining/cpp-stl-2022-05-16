#include "person.hpp"

using namespace std;

Person::Person(const std::string& name, unsigned int age, double salary, Gender gender)
    : name_(name)
    , age_(age)
    , salary_(salary)
    , gender_(gender)
{
}

std::string Person::name() const
{
    return name_;
}

void Person::set_name(const std::string& name)
{
    name_ = name;
}

unsigned int Person::age() const
{
    return age_;
}

void Person::set_age(unsigned int age)
{
    age_ = age;
}

double Person::salary() const
{
    return salary_;
}

void Person::set_salary(double salary)
{
    salary_ = salary;
}

Gender Person::gender() const
{
    return gender_;
}

void Person::set_gender(Gender gender)
{
    gender_ = gender;
}

ostream& operator<<(ostream& out, const Person& p)
{
    out << "Person(name = " << p.name() << ", age = " << p.age() << ", salary = " << p.salary()
        << ", gender = " << ((p.gender() == Gender::male) ? "Male" : "Female") << ")";

    return out;
}
