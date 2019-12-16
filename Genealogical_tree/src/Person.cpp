#include "Person.h"

Person::Person():Person("John", "Doe", 1900, 'M')
{
    //ctor
}

Person::Person(std::string _first_name, std::string _last_name, int _birth_year, char _sex)
:first_name{_first_name}
,last_name{_last_name}
,birth_year{_birth_year}
,sex{_sex}
{
};

Person::~Person()
{
    //dtor
}
