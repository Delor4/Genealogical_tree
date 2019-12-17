#include "GenTree.h"

#include <fstream>

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

void GenTree::save(std::string path)
{
    if(!root) return;
    std::fstream out;
    out.open(path, std::ios::out | std::ios::trunc | std::ios::binary);
    root->save(out);
    out.close();
}
bool GenTree::load(std::string path)
{
    std::fstream in;
    in.open(path, std::ios::in | std::ios::binary);

    GenTreeItem * g = new GenTreeItem();
    g->load(in);
    in.close();
    delete root;
    root = g;
    return true;
}
void GenTree::swap(GenTree &t)
{
    std::swap(root, t.root);
}
int GenTree::get_id(GenTreeItem *i)
{
    int start = 0;
    return root?root->get_id(i, start):-1;
}
