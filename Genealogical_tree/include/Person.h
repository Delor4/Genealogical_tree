#ifndef PERSON_H
#define PERSON_H

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
    virtual ~Person();

    friend std::ostream& operator<<(std::ostream&, const Person&);

    std::string first_name;
    std::string last_name;
    int birth_year;
    char sex;

    void save(std::ostream &os) const;
    bool load(std::istream &os);
protected:
private:
};
}
#endif // PERSON_H
