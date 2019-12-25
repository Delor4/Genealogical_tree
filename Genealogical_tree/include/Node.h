#ifndef GENTREE_NODE_H
#define GENTREE_NODE_H

#include <vector>
#include <fstream>
#include "Person.h"
#include "Console.h"

namespace GenTree
{
class Node
{
public:
    Node();
    Node(Person &);
    virtual ~Node();

    void show();
    bool show(std::string indent, int line, int &curr_line, int skip_lines, int max_lines, Console&);

    Node * add_children(Person &);

    const Person& get_person() const;
    void set_person(Person &);

    void get_siblings(std::vector<Person>&) const;
    void get_childrens(std::vector<Person>&, const Node *skip=nullptr) const;
    void get_grandchildrens(std::vector<Person>&) const;

    int get_id(const Node *, int &curr) const;
    Node * find_by_id(int id, int &curr);

    void remove_by_id(int id);
    void remove_child(Node *);

    Node *get_parent() const;
    Node *get_leftmost_child() const;

    int get_size() const;

    void save_node(std::ostream &os) const;
    bool load_node(std::istream &os);
protected:

private:
    bool has_right_sibling() const;
    int count_childrens() const;

    Person data;
    Node* parent;
    std:: vector <Node*> childrens;
};
}
#endif // GENTREE_NODE_H
