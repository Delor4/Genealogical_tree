#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "RndTree.h"

namespace GenTree
{
RndTree::RndTree()
{
    srand(time(0));
}

Tree RndTree::get_next_tree()
{
    Tree tmp;
    init_tree(tmp);
    return tmp;
}

struct first_name
{
    std::string name;
    int prob;
};
struct last_name
{
    std::string m_name;
    std::string f_name;
};

#include "../gen_names.hpp"

int rnd_fname(int range, int n)
{
    int out = rand() % range;
    for(int i =1; i< n; i++)
    {
        int x = rand() % range;
        if(x < out)
            out = x;
    }
    return out;
}
int RndTree::kids_nr()
{
    return rand() % (max_childrens + 1);
}
int RndTree::birth_year(int base)
{
    return base + age_for_childrens_low + (rand() % (age_for_childrens_high - age_for_childrens_low));
}
std::string get_rnd_female_firstname()
{
    return female_fnames[rnd_fname(female_fnames.size(),5)].name;
}
std::string get_rnd_female_lastname()
{
    return lastnames[rand() % lastnames.size()].f_name;
}
std::string get_rnd_male_lastname()
{
    return lastnames[rand() % lastnames.size()].m_name;
}
std::string get_rnd_male_firstname()
{
    return male_fnames[rnd_fname(male_fnames.size(),5)].name;
}
std::string get_male_from_female_lastname(std::string lname)
{
    auto it = std::find_if(lastnames.begin(),
                           lastnames.end(),
                           [&] (last_name l)
    {
        return l.f_name.compare(lname)==0;
    }
                          );
    return (*it).m_name;
}
Person  RndTree::rnd_person(Node *p)
{
    return (rand()&1) ?
           Person(get_rnd_female_firstname(),
                  get_rnd_female_lastname(),
                  p ? birth_year(p->get_person().birth_year) : start_time,
                  'F')
           :
           Person(get_rnd_male_firstname(),
                  p ?
                  ((p->get_person().sex != 'M') ? get_male_from_female_lastname(p->get_person().last_name) : p->get_person().last_name)
                  :get_rnd_male_lastname(),
                  p ? birth_year(p->get_person().birth_year) : start_time,
                  'M');

}
void RndTree::add_rnd_child(Tree& tree, Node *p)
{
    Person p1 = rnd_person(p);
    if(p1.birth_year > end_time)
        return;

    Node *i1 = tree.add_person(p, p1);

    int kids = kids_nr();
    for(int i = 0; i < kids; i++)
    {
        add_rnd_child(tree, i1);
    }
}

void RndTree::init_tree(Tree& tree)
{
    add_rnd_child(tree, nullptr);
}

}
