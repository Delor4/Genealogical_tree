#include "Item.h"

#include <algorithm>

Item::Item()
    : parent{ nullptr }
{
}

Item::Item(Person& _p)
    : data{ _p }
    , parent{ nullptr }
{
}

Item::~Item()
{
    for (auto i = childrens.begin(); i != childrens.end(); ++i) {
        delete *i;
    }
}

void Item::show()
{
    std::cout << data << '\n';
    for (auto i : childrens) {
        if (i) {
            i->show();
        }
    }
}
bool Item::show(std::string indent, int line, Menu& menu, int& curr_line, Console& console)
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

Item* Item::add_children(Person& p)
{
    Item* i = new Item(p);
    i->parent = this;
    childrens.push_back(i);
    return i;
}

bool Item::has_right_sibling() const
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

int Item::get_size() const
{
    static auto get_item_size = [](int a, Item* b) {
        return a + (b ? b->get_size() : 0);
    };
    return std::accumulate(childrens.begin(), childrens.end(), 1, get_item_size);
}
int Item::count_childrens() const
{
    static auto count_item_childrens = [](int a, Item* b) {
        return a + (b ? 1 : 0);
    };
    return std::accumulate(childrens.begin(), childrens.end(), 0, count_item_childrens);
}
Item* Item::find_by_id(int id, int& curr)
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
Item* Item::get_parent() const
{
    return parent;
}
void Item::remove_child(Item* c)
{
    for (auto i = childrens.begin(); i != childrens.end(); ++i) {
        if (*i == c) {
            *i = nullptr;
            delete c;
            return;
        }
    }
}
const Person& Item::get_person() const
{
    return data;
}
void Item::set_person(Person& p)
{
    data = p;
}
void Item::save(std::ostream& os) const
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
bool Item::load(std::istream& os)
{
    data.load(os);
    short tmp;
    os.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
    for (int i = 0; i < tmp; ++i) {
        Item* g = new Item();
        g->load(os);
        g->parent = this;
        childrens.push_back(g);
    }
    return true;
}
int Item::get_id(const Item* t, int& curr) const
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
Item* Item::get_leftmost_child() const
{
    for (auto i : childrens) {
        if (i)
            return i;
    }
    return nullptr;
}
void Item::get_siblings(std::vector<Person>& v) const
{
    if(parent) parent->get_childrens(v, this);
}
void Item::get_childrens(std::vector<Person>& v, const Item *skip) const
{
    for (auto &i : childrens) {
        if (i && i != skip)
            v.push_back(i->get_person());
    }
}
void Item::get_grandchildrens(std::vector<Person>& v) const
{
    for (auto i : childrens) {
        if (i)
            i->get_childrens(v);
    }
}
