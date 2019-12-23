#ifndef GENTREE_ITEM_H
#define GENTREE_ITEM_H

#include <vector>
#include <fstream>
#include "Person.h"
#include "Console.h"

namespace GenTree
{
class Item
{
public:
    Item();
    Item(Person &);
    virtual ~Item();

    void show();
    bool show(std::string indent, int line, int &curr_line, int skip_lines, int max_lines, Console&);

    Item * add_children(Person &);

    const Person& get_person() const;
    void set_person(Person &);

    void get_siblings(std::vector<Person>&) const;
    void get_childrens(std::vector<Person>&, const Item *skip=nullptr) const;
    void get_grandchildrens(std::vector<Person>&) const;

    int get_id(const Item *, int &curr) const;
    Item * find_by_id(int id, int &curr);

    void remove_by_id(int id);
    void remove_child(Item *);

    Item *get_parent() const;
    Item *get_leftmost_child() const;

    int get_size() const;

    void save(std::ostream &os) const;
    bool load(std::istream &os);
protected:

private:
    bool has_right_sibling() const;
    int count_childrens() const;

    Person data;
    Item* parent;
    std:: vector <Item*> childrens;
};
}
#endif // GENTREE_ITEM_H
