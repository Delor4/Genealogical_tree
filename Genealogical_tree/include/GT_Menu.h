#ifndef GT_MENU_H
#define GT_MENU_H

#include <string>
#include <vector>

enum MENU_ITEMS {
            NONE, ADD_PERSON, ADD_CHILDREN, EDIT_PERSON, DELETE_PERSON, DELETE_TREE, SHOW_CHILDRENS, SHOW_TREE, SAVE, LOAD, EXIT, ERROR
        };


struct GT_MenuItem {
    MENU_ITEMS ID;
    std::string label;
    std::vector<int> short_keys;
    bool disabled;
};

class GT_Menu
{
    public:

        GT_Menu();
        virtual ~GT_Menu();

        void show();
        MENU_ITEMS get_option();

    protected:

    private:
    std::vector<GT_MenuItem> items = {
        {ADD_PERSON,    "1 - dodaj osobe w drzewie",       {'1'}, false},
        {ADD_CHILDREN,  "2 - dodaj dziecko",               {'2'}, false},
        {EDIT_PERSON,   "3 - modyfikuj osobe w drzewie",   {'3'}, false},
        {SHOW_CHILDRENS,"4 - wypisz dzieci",               {'4'}, false},
        {SHOW_TREE,     "5 - wypisz cale drzewo",          {'5'}, false},
        {DELETE_PERSON, "6 - usun osobe",                  {'6'}, false},
        {DELETE_TREE,   "7 - usun drzewo",                 {'7'}, false},
        {SAVE,          "8 - zapisz drzewo",               {'8'}, false},
        {LOAD,          "9 - odczytaj drzewo",             {'9'}, false},
        {EXIT,          "0 - zakoncz program",             {'0'}, false},
    };
};

#endif // GT_MENU_H
