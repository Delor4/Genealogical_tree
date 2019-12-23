#include "Tree.h"

#include <fstream>

Tree::Tree()
    : root{ nullptr }
{
}

Tree::~Tree()
{
    delete root;
}

GenTreeItem* Tree::add_person(GenTreeItem* r, Person& p)
{
    if (r == nullptr) { //add to root of tree
        delete root;
        return root = new GenTreeItem(p);
    }
    return r->add_children(p);
}

void Tree::show() const
{
    if (root)
        root->show();
}

void Tree::show(std::string indent, int line, GenTreeMenu& menu, Console& console) const
{
    int start = 0;
    if (root)
        root->show(indent, line, menu, start, console);
}

int Tree::get_size() const
{
    return root ? root->get_size() : 0;
}

void Tree::remove_by_id(int id)
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

GenTreeItem* Tree::find_by_id(int id) const
{
    int start = 0;
    return root ? root->find_by_id(id, start) : nullptr;
}

void Tree::set_person(GenTreeItem* i, Person& p)
{
    if (i)
        i->set_person(p);
}

void Tree::save(std::string path) const
{
    if (!root)
        return;
    std::fstream out;
    out.open(path, std::ios::out | std::ios::trunc | std::ios::binary);
    root->save(out);
    out.close();
}
bool Tree::load(std::string path)
{
    std::fstream in;
    in.open(path, std::ios::in | std::ios::binary);

    if(!in.good()){
        in.close();
        return false;
    }

    GenTreeItem* g = new GenTreeItem();
    g->load(in);

    delete root;
    root = g;
    return true;

}
void Tree::swap(Tree& t)
{
    std::swap(root, t.root);
}
int Tree::get_id(GenTreeItem* i) const
{
    int start = 0;
    return root ? root->get_id(i, start) : -1;
}
