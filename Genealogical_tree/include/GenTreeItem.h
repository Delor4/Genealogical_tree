#ifndef GENTREEITEM_H
#define GENTREEITEM_H

#include <vector>
#include "Person.h"
#include "GT_Menu.h"

class GenTreeItem
{
    public:
        GenTreeItem();
        GenTreeItem(Person &);
        virtual ~GenTreeItem();

        void show();
        void show(std::string indent, int line, GT_Menu &menu, int curr_line);
        GenTreeItem * add_children(Person &);

    protected:

    private:
        bool has_right_sibling();

        Person data;
        GenTreeItem* parent;
        std:: vector <GenTreeItem*> childrens;
};

#endif // GENTREEITEM_H
