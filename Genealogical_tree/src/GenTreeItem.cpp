#include "GenTreeItem.h"

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
    std::cout << data << '\n';
    for(auto i: childrens){
        if(i) i->show();
    }

}
GenTreeItem * GenTreeItem::add_children(Person &p)
{
    GenTreeItem *i = new GenTreeItem(p);
    i->parent = this;
    childrens.push_back(i);
}
