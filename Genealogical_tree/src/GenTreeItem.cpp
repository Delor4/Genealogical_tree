#include "GenTreeItem.h"

#include <algorithm>

GenTreeItem::GenTreeItem()
    : parent{ nullptr }
{
}

GenTreeItem::GenTreeItem(Person& _p)
    : data{ _p }
    , parent{ nullptr }
{
}

GenTreeItem::~GenTreeItem()
{
    for (auto i = childrens.begin(); i != childrens.end(); ++i) {
        delete *i;
    }
    #ifdef _DEBUG_
        std::cout << "GenTreeItem removed.\n";
    #endif // __DEBUG

}

void GenTreeItem::show()
{
    std::cout << data << '\n';
    for (auto i : childrens) {
        if (i) {
            i->show();
        }
    }
}
bool GenTreeItem::show(std::string indent, int line, GT_Menu& menu, int& curr_line, Console& console)
{
    if (curr_line == 0) {
        if (menu.get_skip_lines() == 0) {
            std::cout << "O\n";
        }
        else {
            std::cout << "^^^\n";
        }
    }
    if ((curr_line - menu.get_skip_lines()) >= menu.get_max_lines()) {
        std::cout << "vvv\n";
        return true;
    }

    if (menu.get_skip_lines() <= curr_line) {
        std::cout << indent << (has_right_sibling() ? "\xc3" : "\xc0") << " ";

        WORD old_attr = 0;
        if (curr_line == line) {
            old_attr = console.set_text_attr(BACKGROUND_INTENSITY);
        }

        std::cout << data;

        if (curr_line == line) {
            console.set_text_attr(old_attr);
        }

        std::cout << '\n';
    }

    std::string add_indent = (has_right_sibling() ? "\xb3 " : "  ");

    for (auto i : childrens) {
        if (i && i->show(indent + add_indent, line, menu, ++curr_line, console))
            return true;
    }
    return false;
}

GenTreeItem* GenTreeItem::add_children(Person& p)
{
    GenTreeItem* i = new GenTreeItem(p);
    i->parent = this;
    childrens.push_back(i);
    return i;
}

bool GenTreeItem::has_right_sibling() const
{
    if (parent) {
        auto it = std::find(parent->childrens.begin(), parent->childrens.end(), this);
        while (++it != parent->childrens.end()) {
            if (*it != nullptr)
                return true;
        }
    }
    return false;
}

int GenTreeItem::get_size() const
{
    static auto get_item_size = [](int a, GenTreeItem* b) {
        return a + (b ? b->get_size() : 0);
    };
    return std::accumulate(childrens.begin(), childrens.end(), 1, get_item_size);
}
int GenTreeItem::count_childrens() const
{
    static auto count_item_childrens = [](int a, GenTreeItem* b) {
        return a + (b ? 1 : 0);
    };
    return std::accumulate(childrens.begin(), childrens.end(), 0, count_item_childrens);
}
GenTreeItem* GenTreeItem::find_by_id(int id, int& curr)
{
    if (id == curr)
        return this;
    for (auto i : childrens) {
        if (i) {
            auto f = i->find_by_id(id, ++curr);
            if (f)
                return f;
        }
    }
    return nullptr;
}
GenTreeItem* GenTreeItem::get_parent() const
{
    return parent;
}
void GenTreeItem::remove_child(GenTreeItem* c)
{
    for (auto i = childrens.begin(); i != childrens.end(); ++i) {
        if (*i == c) {
            *i = nullptr;
            delete c;
            return;
        }
    }
}
const Person& GenTreeItem::get_person() const
{
    return data;
}
void GenTreeItem::set_person(Person& p)
{
    data = p;
}
void GenTreeItem::save(std::ostream& os) const
{
    data.save(os);
    short tmp;
    tmp = count_childrens();
    os.write(reinterpret_cast<const char*>(&tmp), sizeof(tmp));
    for (auto &i : childrens) {
        if (i)
            i->save(os);
    }
}
bool GenTreeItem::load(std::istream& os)
{
    data.load(os);
    short tmp;
    os.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
    for (int i = 0; i < tmp; ++i) {
        GenTreeItem* g = new GenTreeItem();
        g->load(os);
        g->parent = this;
        childrens.push_back(g);
    }
    return true;
}
int GenTreeItem::get_id(const GenTreeItem* t, int& curr) const
{
    if (this == t)
        return curr;
    int out;
    for (auto i : childrens) {
        if (i && (out = i->get_id(t, ++curr)) >= 0)
            return out;
    }
    return -1;
}
GenTreeItem* GenTreeItem::get_leftmost_child() const
{
    for (auto i : childrens) {
        if (i)
            return i;
    }
    return nullptr;
}
void GenTreeItem::get_siblings(std::vector<Person>& v) const
{
    if(parent) parent->get_childrens(v, this);
}
void GenTreeItem::get_childrens(std::vector<Person>& v, const GenTreeItem *skip) const
{
    for (auto &i : childrens) {
        if (i && i != skip)
            v.push_back(i->get_person());
    }
}
void GenTreeItem::get_grandchildrens(std::vector<Person>& v) const
{
    for (auto i : childrens) {
        if (i)
            i->get_childrens(v);
    }
}
