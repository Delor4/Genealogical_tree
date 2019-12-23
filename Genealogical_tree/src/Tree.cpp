#include "Tree.h"

#include <fstream>
namespace GenTree
{
Tree::Tree()
    : root{ nullptr }
{
}

Tree::~Tree()
{
    delete root;
}

Node* Tree::add_person(Node* r, Person& p)
{
    if (r == nullptr)   //add to root of tree
    {
        delete root;
        return root = new Node(p);
    }
    return r->add_children(p);
}

void Tree::show_tree() const
{
    if (root)
        root->show();
}

void Tree::show_tree_indented(std::string indent, int line, int skip_lines, int max_lines, Console& console) const
{
    int start = 0;
    if (root)
        root->show(indent, line, start, skip_lines, max_lines, console);
}

int Tree::get_size() const
{
    return root ? root->get_size() : 0;
}

void Tree::remove_node_by_id(int id)
{
    Node* p = find_node_by_id(id);
    if (!p)
        return;
    if (p == root)
    {
        root = nullptr;
        delete p;
    }
    else
    {
        p->get_parent()->remove_child(p);
    }
}

Node* Tree::find_node_by_id(int id) const
{
    int start = 0;
    return root ? root->find_by_id(id, start) : nullptr;
}

void Tree::set_person(Node* i, Person& p)
{
    if (i)
        i->set_person(p);
}

void Tree::save_tree(std::string path) const
{
    if (!root)
        return;
    std::fstream out;
    out.open(path, std::ios::out | std::ios::trunc | std::ios::binary);
    root->save_node(out);
    out.close();
}
bool Tree::load_tree(std::string path)
{
    std::fstream in;
    in.open(path, std::ios::in | std::ios::binary);

    if(!in.good())
    {
        in.close();
        return false;
    }

    Node* g = new Node();
    g->load_node(in);

    delete root;
    root = g;
    return true;

}
void Tree::swap(Tree& t)
{
    std::swap(root, t.root);
}
int Tree::get_node_id(Node* i) const
{
    int start = 0;
    return root ? root->get_id(i, start) : -1;
}
}
