#ifndef GT_MENU_H
#define GT_MENU_H

#include <string>
#include <vector>
#include <windows.h>

enum MENU_ITEMS {
            NONE,
            ADD_PERSON,
            ADD_CHILDREN,
            EDIT_PERSON,
            DELETE_PERSON,
            DELETE_TREE,
            SHOW_CHILDRENS,
            SHOW_TREE,
            SAVE,
            LOAD,
            EXIT,
            GT_ERROR
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

        void gotoxy(int x, int y);
        void cls();
        WORD SetConsoleAttr(WORD attr);
    protected:

    private:
    std::vector<GT_MenuItem> items = {
        {ADD_CHILDREN,  "a - dodaj osobe",                 {'2'}, false},
        {EDIT_PERSON,   "e - modyfikuj osobe",             {'3'}, false},
        {DELETE_PERSON, "d - usun osobe",                  {'6'}, false},
        {SAVE,          "s - zapisz drzewo",               {'8'}, false},
        {LOAD,          "l - odczytaj drzewo",             {'9'}, false},
        {EXIT,          "q - zakoncz program",             {'0', 'q'}, false},
    };
};

#endif // GT_MENU_H
