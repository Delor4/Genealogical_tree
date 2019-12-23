#ifndef GENTREE_TREE_H
#define GENTREE_TREE_H

#include "Item.h"

namespace GenTree
{
class Tree
{
public:
    Tree();
    virtual ~Tree();

    void show() const;
    void show(std::string indent, int line, int skip_lines, int max_lines, Console&) const;

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
}
#endif // GENTREE_TREE_H
