#include "Person.h"

Person::Person()
    : Person("John", "Doe", 1900, 'M')
{
}

Person::Person(std::string _first_name, std::string _last_name, int _birth_year, char _sex)
    : first_name{ _first_name }
    , last_name{ _last_name }
    , birth_year{ _birth_year }
{
    sex = (tolower(_sex) == 'm' ? 'M' : 'K');
};

Person::~Person()
{
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << p.first_name << ' ' << p.last_name << ", " << p.birth_year << ", " << p.sex;
    return os;
}

void Person::save(std::ostream &os) const
{
    short tmp;
    tmp = first_name.length();
    os.write(reinterpret_cast<const char *>(&tmp), sizeof(tmp));
    os << first_name;

    tmp = last_name.length();
    os.write(reinterpret_cast<const char *>(&tmp), sizeof(tmp));
    os << last_name;

    os.write(reinterpret_cast<const char *>(&birth_year), sizeof(birth_year));

    os << sex;
}
std::string read_string(std::istream &os)
{
    short tmp;
    os.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
    char *buff = new char[tmp + 1];
    os.read(buff, tmp);
    buff[tmp] = 0;
    std::string out(buff);
    delete[] buff;
    return out;
}

bool Person::load(std::istream &os)
{
    first_name = read_string(os);
    last_name = read_string(os);

    os.read(reinterpret_cast<char *>(&birth_year), sizeof(birth_year));
    os >> sex;

    return true;
}
