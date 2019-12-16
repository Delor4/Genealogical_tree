#include "Person.h"

Person::Person():Person("John", "Doe", 1900, 'M')
{
    //ctor
}

Person::Person(std::string _first_name, std::string _last_name, int _birth_year, char _sex)
:first_name{_first_name}
,last_name{_last_name}
,birth_year{_birth_year}
{
    sex = (tolower(_sex)=='m'?'M':'K');
};

Person::~Person()
{
    //dtor
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << p.first_name << ' ' << p.last_name << ", " << p.birth_year << ", " << p.sex;
    return os;
}
