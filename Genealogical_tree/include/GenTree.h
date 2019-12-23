#ifndef GENTREE_H
#define GENTREE_H

#include "GenTreeItem.h"

class GenTree {
public:
    GenTree();
    virtual ~GenTree();

    void show() const;
    void show(std::string indent, int line, GenTreeMenu& menu, Console&) const;

    void set_person(GenTreeItem* p, Person&);
    GenTreeItem* add_person(GenTreeItem* p, Person&);

    int get_id(GenTreeItem *) const;

    GenTreeItem* find_by_id(int id) const;
    void remove_by_id(int id);

    int get_size() const;

    void save(std::string path) const;
    bool load(std::string path);

    void swap(GenTree &);

protected:
private:
    GenTreeItem* root;
};

#endif // GENTREE_H
