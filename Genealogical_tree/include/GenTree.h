#ifndef GENTREE_H
#define GENTREE_H

#include "GenTreeItem.h"

class GenTree {
public:
    GenTree();
    virtual ~GenTree();

    void show();
    void show(std::string indent, int line, GT_Menu& menu, Console&);

    void set_person(GenTreeItem* p, Person&);
    GenTreeItem* add_person(GenTreeItem* p, Person&);

    int get_id(GenTreeItem *);

    GenTreeItem* find_by_id(int id);
    void remove_by_id(int id);

    int get_size();

    void save(std::string path);
    bool load(std::string path);

    void swap(GenTree &);

protected:
private:
    GenTreeItem* root;
};

#endif // GENTREE_H
