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
        bool show(std::string indent, int line, GT_Menu &menu, int &curr_line, Console&);

        GenTreeItem * add_children(Person &);

        Person get_person();
        void set_person(Person &);

        void get_siblings(std::vector<Person>&);
        void get_childrens(std::vector<Person>&, GenTreeItem *skip=nullptr);
        void get_grandchildrens(std::vector<Person>&);

        int get_id(GenTreeItem *, int &curr);
        GenTreeItem * find_by_id(int id, int &curr);

        void remove_by_id(int id);
        void remove_child(GenTreeItem *);

        GenTreeItem *get_parent();
        GenTreeItem *get_leftmost_child();

        int get_size();

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
