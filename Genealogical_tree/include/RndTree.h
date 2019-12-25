#ifndef RNDTREE_H
#define RNDTREE_H

#include "Tree.h"

namespace GenTree
{
class RndTree
{
public:
    RndTree();
    virtual ~RndTree() = default;

    Tree get_next_tree();
protected:

private:
    void init_tree(Tree& tree);
    void add_rnd_child(Tree& tree, Node *p);
    int birth_year(int base);
    Person rnd_person(Node *p);

    int kids_nr();

    const int start_time = 1900;
    const int end_time = 2019;
};
}
#endif // RNDTREE_H
