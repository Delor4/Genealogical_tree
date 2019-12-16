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
void GenTreeItem::show(std::string indent)
{
    std::cout << indent << (has_right_sibling()?"\xc3":"\xc0") << " " << data <<'\n';

    std::string add_indent = (has_right_sibling()?"\xb3 ":"  ");

    for(auto i: childrens){
        if(i){
            i->show(indent + add_indent);
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
