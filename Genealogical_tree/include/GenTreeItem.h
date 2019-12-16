#ifndef GENTREEITEM_H
#define GENTREEITEM_H

#include <vector>
#include "Person.h"

class GenTreeItem
{
    public:
        GenTreeItem();
        GenTreeItem(Person &);
        virtual ~GenTreeItem();

        void show();
        GenTreeItem * add_children(Person &);

    protected:

    private:
    GenTreeItem* parent;
    std:: vector <GenTreeItem*> childrens;
    Person data;
};

#endif // GENTREEITEM_H
