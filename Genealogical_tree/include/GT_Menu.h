#ifndef GT_MENU_H
#define GT_MENU_H

#include <string>
#include <vector>
#include <windows.h>

enum MENU_ITEMS {
            NONE,
            ADD_PERSON,
            EDIT_PERSON,
            DELETE_PERSON,
            SAVE,
            LOAD,
            EXIT,
            ARROW_UP,
            ARROW_DOWN,
            GT_ERROR
        };


struct GT_MenuItem {
    MENU_ITEMS ID;
    std::string label;
    std::vector<int> short_keys;
    bool show;
};

class GT_Menu
{
    static const int MAXLINES = 20;

    public:

        GT_Menu();
        virtual ~GT_Menu();

        void show();
        MENU_ITEMS get_option();

        void gotoxy(short x, short y);
        void cls();
        WORD SetConsoleAttr(WORD attr);

        void line_down();
        void line_up();
        void set_curr_max_lines(int);

        int get_curr_line();
        static int get_max_lines(){ return MAXLINES;};
    protected:

    private:
    std::vector<GT_MenuItem> items = {
        {ADD_PERSON,    "a - dodaj osobe",                 {65}, true},
        {EDIT_PERSON,   "e - modyfikuj osobe",             {69, 13}, true},
        {DELETE_PERSON, "d - usun osobe",                  {68}, true},
        {SAVE,          "s - zapisz drzewo",               {83}, true},
        {LOAD,          "l - odczytaj drzewo",             {76}, true},
        {EXIT,          "q - zakoncz program",             {81, 27}, true},
        {ARROW_UP,      "",                                {38}, false},
        {ARROW_DOWN,    "",                                {40}, false},
    };

    int act_line;
    int curr_max_items;

    HANDLE hStdout;

    void check_constrants();
};

#endif // GT_MENU_H
