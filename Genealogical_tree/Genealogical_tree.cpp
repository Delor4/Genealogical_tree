#include <iostream>
#include "GT_Menu.h"
#include "GenTree.h"

using namespace std;

void init_tree(GenTree& tree)
{
    Person p1("Jan", "Kowalski", 1954, 'M');
    GenTreeItem *i1 = tree.add_person(nullptr, p1);

        Person p2("Janina", "Kowalska", 1974, 'K');
        GenTreeItem *i2 = tree.add_person(i1, p2);

        Person p3("Jambrozy", "Kowalski", 1977, 'M');
        GenTreeItem *i3 = tree.add_person(i1, p3);
            Person p4("Grazyna", "Kowalska", 1994, 'K');
            GenTreeItem *i4 = tree.add_person(i3, p4);
}
int main()
{
    GT_Menu menu;
    GenTree tree;
    cout << "Genealogical Tree." << endl;

    init_tree(tree);
    tree.show();


    menu.show();
    menu.get_option();

    return 0;
}
