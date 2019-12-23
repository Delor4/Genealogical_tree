#ifndef GENTREE_H
#define GENTREE_H

#include "Item.h"

class Tree {
public:
    Tree();
    virtual ~Tree();

    void show() const;
    void show(std::string indent, int line, GenTreeMenu& menu, Console&) const;

    void set_person(Item* p, Person&);
    Item* add_person(Item* p, Person&);

    int get_id(Item *) const;

    Item* find_by_id(int id) const;
    void remove_by_id(int id);

    int get_size() const;

    void save(std::string path) const;
    bool load(std::string path);

    void swap(Tree &);

protected:
private:
    Item* root;
};

#endif // GENTREE_H
