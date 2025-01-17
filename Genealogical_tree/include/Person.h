#ifndef GENTREE_PERSON_H
#define GENTREE_PERSON_H

#include <iostream>
#include <string>
#include <fstream>

namespace GenTree
{
class Person
{
public:
    Person();
    Person(std::string, std::string, int, char);
    virtual ~Person() = default;

    friend std::ostream& operator<<(std::ostream&, const Person&);

    std::string first_name;
    std::string last_name;
    int birth_year;
    char sex;

    void save_person(std::ostream &os) const;
    bool load_person(std::istream &os);
protected:
private:
};
}
#endif // GENTREE_PERSON_H
