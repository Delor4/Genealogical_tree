#ifndef GENTREEITEM_H
#define GENTREEITEM_H

#include <vector>
#include <fstream>
#include "Person.h"
#include "GenTreeMenu.h"
#include "Console.h"

class GenTreeItem
{
    public:
        GenTreeItem();
        GenTreeItem(Person &);
        virtual ~GenTreeItem();

        void show();
        bool show(std::string indent, int line, GenTreeMenu &menu, int &curr_line, Console&);

        GenTreeItem * add_children(Person &);

        const Person& get_person() const;
        void set_person(Person &);

        void get_siblings(std::vector<Person>&) const;
        void get_childrens(std::vector<Person>&, const GenTreeItem *skip=nullptr) const;
        void get_grandchildrens(std::vector<Person>&) const;

        int get_id(const GenTreeItem *, int &curr) const;
        GenTreeItem * find_by_id(int id, int &curr);

        void remove_by_id(int id);
        void remove_child(GenTreeItem *);

        GenTreeItem *get_parent() const;
        GenTreeItem *get_leftmost_child() const;

        int get_size() const;

        void save(std::ostream &os) const;
        bool load(std::istream &os);
    protected:

    private:
        bool has_right_sibling() const;
        int count_childrens() const;

        Person data;
        GenTreeItem* parent;
        std:: vector <GenTreeItem*> childrens;
};

#endif // GENTREEITEM_H
