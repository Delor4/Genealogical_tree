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

void GenTree::show(std::string indent, int line, GT_Menu &menu)
{
    int start = 0;
    if(root) root->show(indent, line, menu, start);
}

int GenTree::get_size()
{
    if(root) return root->get_size();
    return 0;
}
