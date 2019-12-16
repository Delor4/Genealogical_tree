#include <iostream>
#include "GT_Menu.h"

using namespace std;

int main()
{
    GT_Menu menu;
    cout << "Genealogical Tree." << endl;

    menu.show();
    menu.get_option();

    return 0;
}
