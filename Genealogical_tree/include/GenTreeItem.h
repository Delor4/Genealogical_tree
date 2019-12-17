#ifndef GENTREEITEM_H
#define GENTREEITEM_H

#include <vector>
#include <fstream>
#include "Person.h"
#include "GT_Menu.h"

class GenTreeItem
{
    public:
        GenTreeItem();
        GenTreeItem(Person &);
        virtual ~GenTreeItem();

        void show();
        bool show(std::string indent, int line, GT_Menu &menu, int &curr_line);
        GenTreeItem * add_children(Person &);

        int get_size();
        void remove_by_id(int id);
        GenTreeItem * find_by_id(int id, int &curr);
        GenTreeItem *get_parent();
        void remove_child(GenTreeItem *);
        Person get_person();
        void set_person(Person &);

        void save(std::ostream &os);
        bool load(std::istream &os);
    protected:

    private:
        bool has_right_sibling();
        int count_childrens();

        Person data;
        GenTreeItem* parent;
        std:: vector <GenTreeItem*> childrens;
};

#endif // GENTREEITEM_H
