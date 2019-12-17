#ifndef GENTREE_H
#define GENTREE_H

#include "GenTreeItem.h"

class GenTree {
public:
    GenTree();
    virtual ~GenTree();

    GenTreeItem* add_person(GenTreeItem* p, Person&);

    void show();
    void show(std::string indent, int line, GT_Menu& menu);
    int get_size();
    void remove_by_id(int id);
    GenTreeItem* find_by_id(int id);
    void set_person(GenTreeItem* p, Person&);

    void save(std::string path);

protected:
private:
    GenTreeItem* root;
};

#endif // GENTREE_H
