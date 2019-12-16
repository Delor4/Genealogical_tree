#include <iostream>
#include <windows.h>

#include "GT_Menu.h"
#include "GenTree.h"

using namespace std;

void init_tree(GenTree& tree)
{
    Person p1("Jan", "Kowalski", 1954, 'M');
    GenTreeItem *i1 = tree.add_person(nullptr, p1);

        Person p2("Janina", "Kowalska", 1974, 'K');
        GenTreeItem *i2 = tree.add_person(i1, p2);
            Person p5("Dorota", "Kowalska", 1994, 'K');
            GenTreeItem *i5 = tree.add_person(i2, p5);
            Person p6("Daria", "Kowalska", 1994, 'K');
            GenTreeItem *i6 = tree.add_person(i2, p6);

        Person p3("Jambrozy", "Kowalski", 1977, 'M');
        GenTreeItem *i3 = tree.add_person(i1, p3);
            Person p4("Grazyna", "Kowalska", 1994, 'K');
            GenTreeItem *i4 = tree.add_person(i3, p4);
}

int main()
{
    GT_Menu menu;
    GenTree tree;

    init_tree(tree);
    while(true){
    menu.set_max_lines(tree.get_size());
    menu.cls();
    cout << "Drzewo genealogiczne." << endl;

    menu.show();

    cout << "O" << endl;
    tree.show("", menu.get_curr_line(), menu);
    std::cout.flush();
    Sleep(10);

    switch(menu.get_option()){
        case EXIT:
            exit(0);
        case ADD_PERSON:
        case EDIT_PERSON:
        case DELETE_PERSON:
            tree.remove_by_id(menu.get_curr_line());
            break;
        case LOAD:
        case SAVE:
            break;
        case ARROW_DOWN:
            menu.line_down();
            break;
        case ARROW_UP:
            menu.line_up();
            break;
        default:
            break;
        };
    }
    return 0;
}
