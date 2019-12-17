#include "GenTree.h"

GenTree::GenTree()
    : root{ nullptr }
{
}

GenTree::~GenTree()
{
    delete root;
}

GenTreeItem* GenTree::add_person(GenTreeItem* r, Person& p)
{
    if (r == nullptr) { //add to root of tree
        delete root;
        return root = new GenTreeItem(p);
    }
    return r->add_children(p);
}

void GenTree::show()
{
    if (root)
        root->show();
}

void GenTree::show(std::string indent, int line, GT_Menu& menu)
{
    int start = 0;
    if (root)
        root->show(indent, line, menu, start);
}

int GenTree::get_size()
{
    return root ? root->get_size() : 0;
}

void GenTree::remove_by_id(int id)
{
    GenTreeItem* p = find_by_id(id);
    if (!p)
        return;
    if (p == root) {
        root = nullptr;
        delete p;
    }
    else {
        p->get_parent()->remove_child(p);
    }
}

GenTreeItem* GenTree::find_by_id(int id)
{
    int start = 0;
    return root ? root->find_by_id(id, start) : nullptr;
}

void GenTree::set_person(GenTreeItem* i, Person& p)
{
    if (i)
        i->set_person(p);
}
