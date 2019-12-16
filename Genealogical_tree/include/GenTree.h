#ifndef GENTREE_H
#define GENTREE_H

#include "GenTreeItem.h"

class GenTree
{
    public:
        GenTree();
        virtual ~GenTree();

        GenTreeItem * add_person(GenTreeItem *p,Person &);

        void show();
        void show(std::string indent);
    protected:

    private:
        GenTreeItem *root;
};

#endif // GENTREE_H