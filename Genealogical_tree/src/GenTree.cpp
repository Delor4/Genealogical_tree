#include "GenTree.h"

GenTree::GenTree()
{
    //ctor
}

GenTree::~GenTree()
{
    delete root;
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
void GenTree::remove_by_id(int id)
{
    GenTreeItem * p = find_by_id(id);
    if(!p) return;
    if(p == root){
        root = nullptr;
        delete p;
    }else{
        p->get_parent()->remove_child(p);
    }
}
GenTreeItem * GenTree::find_by_id(int id)
{
    int start = 0;
    if(root) return root->find_by_id(id, start);
    return nullptr;
}
