#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <string>
#include <vector>

enum class Gender
{
    male,
    female
};

class Person
{
    std::string name_;
    unsigned int age_;
    double salary_;
    Gender gender_;

public:
    Person(const std::string& name, unsigned int age, double salary, Gender gender);

    std::string name() const;
    void set_name(const std::string& name);

    unsigned int age() const;
    void set_age(unsigned int age);

    double salary() const;
    void set_salary(double salary);

    Gender gender() const;
    void set_gender(Gender gender);
};

std::ostream& operator<<(std::ostream& out, const Person& p);

#endif
