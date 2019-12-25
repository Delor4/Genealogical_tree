#include "Node.h"

#include <algorithm>

namespace GenTree
{
Node::Node()
    : parent{ nullptr }
{
}

Node::Node(Person& _p)
    : data{ _p }
    , parent{ nullptr }
{
}

Node::~Node()
{
    for (auto i = childrens.begin(); i != childrens.end(); ++i)
    {
        delete *i;
    }
}

void Node::show()
{
    std::cout << data << '\n';
    for (auto i : childrens)
    {
        if (i)
        {
            i->show();
        }
    }
}
bool Node::show(std::string indent, int line, int& curr_line, int skip_lines, int max_lines, Console& console)
{
    if (curr_line == 0)
    {
        if (skip_lines == 0)
        {
            std::cout << "O\n";
        }
        else
        {
            std::cout << "^^^\n";
        }
    }
    if ((curr_line - skip_lines) >= max_lines)
    {
        std::cout << "vvv\n";
        return true;
    }

    if (skip_lines <= curr_line)
    {
        std::cout << indent << (has_right_sibling() ? "\xc3" : "\xc0") << " ";

        WORD old_attr = 0;
        if (curr_line == line)
        {
            old_attr = console.set_text_attr(BACKGROUND_INTENSITY);
        }

        std::cout << data;

        if (curr_line == line)
        {
            console.set_text_attr(old_attr);
        }

        std::cout << '\n';
    }

    std::string add_indent = (has_right_sibling() ? "\xb3 " : "  ");

    for (auto i : childrens)
    {
        if (i && i->show(indent + add_indent, line, ++curr_line, skip_lines, max_lines, console))
            return true;
    }
    return false;
}

Node* Node::add_children(Person& p)
{
    Node* i = new Node(p);
    i->parent = this;
    childrens.push_back(i);
    return i;
}

bool Node::has_right_sibling() const
{
    if (parent)
    {
        auto it = std::find(parent->childrens.begin(), parent->childrens.end(), this);
        while (++it != parent->childrens.end())
        {
            if (*it != nullptr)
                return true;
        }
    }
    return false;
}

int Node::get_size() const
{
    static auto get_item_size = [](int a, Node* b)
    {
        return a + (b ? b->get_size() : 0);
    };
    return std::accumulate(childrens.begin(), childrens.end(), 1, get_item_size);
}
int Node::count_childrens() const
{
    static auto count_item_childrens = [](int a, Node* b)
    {
        return a + (b ? 1 : 0);
    };
    return std::accumulate(childrens.begin(), childrens.end(), 0, count_item_childrens);
}
Node* Node::find_by_id(int id, int& curr)
{
    if (id == curr)
        return this;
    for (auto i : childrens)
    {
        if (i)
        {
            auto f = i->find_by_id(id, ++curr);
            if (f)
                return f;
        }
    }
    return nullptr;
}
Node* Node::get_parent() const
{
    return parent;
}
void Node::remove_child(Node* c)
{
    for (auto i = childrens.begin(); i != childrens.end(); ++i)
    {
        if (*i == c)
        {
            *i = nullptr;
            delete c;
            return;
        }
    }
}
const Person& Node::get_person() const
{
    return data;
}
void Node::set_person(Person& p)
{
    data = p;
}
void Node::save_node(std::ostream& os) const
{
    data.save_person(os);
    short tmp;
    tmp = count_childrens();
    os.write(reinterpret_cast<const char*>(&tmp), sizeof(tmp));
    for (auto &i : childrens)
    {
        if (i)
            i->save_node(os);
    }
}
bool Node::load_node(std::istream& os)
{
    data.load_person(os);
    short tmp;
    os.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
    for (int i = 0; i < tmp; ++i)
    {
        Node* g = new Node();
        g->load_node(os);
        g->parent = this;
        childrens.push_back(g);
    }
    return true;
}
int Node::get_id(const Node* t, int& curr) const
{
    if (this == t)
        return curr;
    int out;
    for (auto i : childrens)
    {
        if (i && (out = i->get_id(t, ++curr)) >= 0)
            return out;
    }
    return -1;
}
Node* Node::get_leftmost_child() const
{
    for (auto i : childrens)
    {
        if (i)
            return i;
    }
    return nullptr;
}
void Node::get_siblings(std::vector<Person>& v) const
{
    if(parent)
        parent->get_childrens(v, this);
}
void Node::get_childrens(std::vector<Person>& v, const Node *skip) const
{
    for (auto &i : childrens)
    {
        if (i && i != skip)
            v.push_back(i->get_person());
    }
}
void Node::get_grandchildrens(std::vector<Person>& v) const
{
    for (auto i : childrens)
    {
        if (i)
            i->get_childrens(v);
    }
}
}
