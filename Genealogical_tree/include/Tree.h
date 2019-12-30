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

    void show_tree() const;
    void show_tree_indented(std::string indent, int line, int skip_lines, int max_lines, Console&) const;

    void set_person(Node* p, Person&);
    Node* add_person(Node* p, Person&);

    int get_node_id(Node *) const;

    Node* find_node_by_id(int id) const;
    void remove_node_by_id(int id);

    int get_size() const;

    void save_tree(std::string path) const;
    bool load_tree(std::string path);

    void swap(Tree &);

protected:
private:
    const char *save_tag_str = "GT_1.0";

    void save_tag(std::fstream &os) const;
    bool check_tag(std::fstream &is) const;

    Node* root;
};
}
#endif // GENTREE_TREE_H
