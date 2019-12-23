#ifndef GENTREE_TREE_H
#define GENTREE_TREE_H

#include "Node.h"

namespace GenTree
{
class Tree
{
public:
    Tree();
    virtual ~Tree();

    void show() const;
    void show(std::string indent, int line, int skip_lines, int max_lines, Console&) const;

    void set_person(Node* p, Person&);
    Node* add_person(Node* p, Person&);

    int get_id(Node *) const;

    Node* find_by_id(int id) const;
    void remove_by_id(int id);

    int get_size() const;

    void save(std::string path) const;
    bool load(std::string path);

    void swap(Tree &);

protected:
private:
    Node* root;
};
}
#endif // GENTREE_TREE_H
