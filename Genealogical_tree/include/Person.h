#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person
{
    public:
        Person();
        Person(std::string, std::string, int, char);
        virtual ~Person();

        friend std::ostream& operator<<(std::ostream&, const Person&);

    std::string first_name;
    std::string last_name;
    int birth_year;
    char sex;

    protected:

    private:
};

#endif // PERSON_H
