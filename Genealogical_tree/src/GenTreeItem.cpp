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
bool GenTreeItem::show(std::string indent, int line, GT_Menu& menu, int& curr_line)
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
            old_attr = menu.set_text_attr(BACKGROUND_INTENSITY);
        }

        std::cout << data;

        if (curr_line == line) {
            menu.set_text_attr(old_attr);
        }

        std::cout << '\n';
    }

    std::string add_indent = (has_right_sibling() ? "\xb3 " : "  ");

    for (auto i : childrens) {
        if (i && i->show(indent + add_indent, line, menu, ++curr_line))
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

bool GenTreeItem::has_right_sibling()
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
auto get_item_size = [](int a, GenTreeItem* b) {
    return a + (b ? b->get_size() : 0);
};

int GenTreeItem::get_size()
{
    return std::accumulate(childrens.begin(), childrens.end(), 1, get_item_size);
}
auto count_item_childrens = [](int a, GenTreeItem* b) {
    return a + (b ? 1 : 0);
};
int GenTreeItem::count_childrens()
{
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
GenTreeItem* GenTreeItem::get_parent()
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
Person GenTreeItem::get_person()
{
    return data;
}
void GenTreeItem::set_person(Person& p)
{
    data = p;
}
void GenTreeItem::save(std::ostream &os)
{
    data.save(os);
    short tmp;
    tmp = count_childrens();
    os.write(reinterpret_cast<const char *>(&tmp), sizeof(tmp));
    for(auto i: childrens){
        if(i) i->save(os);
    }
}
