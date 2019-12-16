#ifndef GT_MENU_H
#define GT_MENU_H

#include <string>
#include <vector>

struct GT_MenuItem {
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

    protected:

    private:
    std::vector<GT_MenuItem> items = {
        {"1 - dodaj osobe w drzewie",       {1}, false},
        {"2 - dodaj przodka",               {2}, false},
        {"3 - modyfikuj osobe w drzewie",   {3}, false},
        {"4 - wypisz rodzicow",             {4}, false},
        {"5 - wypisz cale drzewo",          {5}, false},
        {"6 - usun osobe",                  {6}, false},
        {"7 - usun drzewo",                 {7}, false},
        {"8 - zapisz drzewo",               {8}, false},
        {"9 - odczytaj drzewo",             {9}, false},
        {"0 - zakoncz program",             {0}, false},
    };
};

#endif // GT_MENU_H
