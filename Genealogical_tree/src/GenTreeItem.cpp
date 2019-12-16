#include "GenTreeItem.h"

#include <algorithm>

GenTreeItem::GenTreeItem()
:parent{nullptr}
{
    //ctor
}

GenTreeItem::GenTreeItem(Person &_p)
:data{_p}
,parent{nullptr}
{
};

GenTreeItem::~GenTreeItem()
{
    //dtor
}

void GenTreeItem::show()
{
    std::cout << data <<'\n';
    for(auto i: childrens){
        if(i){
            i->show();

        }
    }
}
void GenTreeItem::show(std::string indent, int line, GT_Menu &menu,int &curr_line)
{
    std::cout << indent << (has_right_sibling()?"\xc3":"\xc0") << " ";
    WORD old_attr;
    if(curr_line == line){
        old_attr = menu.SetConsoleAttr(BACKGROUND_INTENSITY);
    }
    std::cout << data;
    if(curr_line == line){
        menu.SetConsoleAttr(old_attr);
    }
    std::cout << '\n';

    std::string add_indent = (has_right_sibling()?"\xb3 ":"  ");

    for(auto i: childrens){
        if(i){
            i->show(indent + add_indent, line, menu, ++curr_line);
        }
    }

}

GenTreeItem * GenTreeItem::add_children(Person &p)
{
    GenTreeItem *i = new GenTreeItem(p);
    i->parent = this;
    childrens.push_back(i);
    return i;
}

bool GenTreeItem::has_right_sibling()
{
    if(parent){
        auto it = std::find(parent->childrens.begin(), parent->childrens.end(), this);
        while(++it != parent->childrens.end()){
            if(*it!= nullptr) return true;
        }
    }
    return false;
}
auto get_item_size = [](int a, GenTreeItem* b) {
                         return a + (b?b->get_size():0);
                     };



int GenTreeItem::get_size()
{
    return std::accumulate(childrens.begin(), childrens.end(), 1, get_item_size);
}
GenTreeItem * GenTreeItem::find_by_id(int id, int &curr)
{
    if(id==curr) return this;
    for(auto i: childrens){
        if(i){
            auto f = i->find_by_id(id, ++curr);
            if(f) return f;
        }
    }
    return nullptr;
}
GenTreeItem * GenTreeItem::get_parent()
{
    return parent;
}
void GenTreeItem::remove_child(GenTreeItem *c)
{
    for(auto i=childrens.begin(); i!=childrens.end();++i)
    {
        if(*i == c){
            *i = nullptr;
            delete c;
            return;
        }
    }
}
