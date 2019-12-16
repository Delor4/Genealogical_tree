#include "GenTree.h"

GenTree::GenTree()
{
    //ctor
}

GenTree::~GenTree()
{
    //dtor
}

GenTreeItem * GenTree::add_person(GenTreeItem *r,Person &p)
{
    //TODO: root!=nullpointer and r==null
    if(r==nullptr){//add to root of tree
        return root = new GenTreeItem(p);
    }
    return r->add_children(p);
}

void GenTree::show()
{
    if(root) root->show();
}
