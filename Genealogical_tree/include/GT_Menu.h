#ifndef GT_MENU_H
#define GT_MENU_H

#include <string>
#include <vector>
#include <windows.h>

class GT_Menu

    {

public:
    static const int MAXLINES = 24;
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
        ARROW_LEFT,
        ARROW_RIGHT,
        GT_ERROR
    };
    GT_Menu();
    virtual ~GT_Menu();

    void show();
    MENU_ITEMS get_option();

    void gotoxy(short x, short y);
    void cls();
    WORD set_text_attr(WORD attr);

    void line_down();
    void line_up();
    void set_curr_max_lines(int);

    int get_curr_line();
    void set_curr_line(int line);
    int get_skip_lines();
    static int get_max_lines() { return MAXLINES; };
protected:
private:
    struct GT_MenuItem {
        MENU_ITEMS ID;
        std::string label;
        std::vector<int> short_keys;
        bool show;
    };
    std::vector<GT_MenuItem> items = {
        { ADD_PERSON,   "a - dodaj potomka",    { 65, VK_INSERT },      true },
        { EDIT_PERSON,  "e - modyfikuj osobe",  { 69, VK_RETURN },      true },
        { DELETE_PERSON, "d - usun osobe",      { 68, VK_DELETE },      true },
        { SAVE,         "s - zapisz drzewo",    { 83 },                 true },
        { LOAD,         "l - odczytaj drzewo",  { 76 },                 true },
        { EXIT,         "q - zakoncz program",  { 81, VK_ESCAPE },      true },
        { ARROW_UP,     "",                     { VK_UP },              false },
        { ARROW_DOWN,   "",                     { VK_DOWN },            false },
        { ARROW_LEFT,   "",                     { VK_LEFT },            false },
        { ARROW_RIGHT,  "",                     { VK_RIGHT },           false },
    };

    int act_line;
    int curr_max_items;
    int skip_lines;

    HANDLE h_stdout;
    HANDLE h_stdin;

    void check_constraints();
};

#endif // GT_MENU_H
