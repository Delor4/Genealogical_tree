#include <iostream>
#include "GT_Menu.h"
#include "GenTree.h"

using namespace std;

int main()
{
    GT_Menu menu;
    GenTree tree;
    cout << "Genealogical Tree." << endl;

    menu.show();
    menu.get_option();

    return 0;
}
