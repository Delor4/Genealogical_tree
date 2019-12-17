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
        { ADD_PERSON,   "a - dodaj potomka",    { 65 },     true },
        { EDIT_PERSON,  "e - modyfikuj osobe",  { 69, 13 }, true },
        { DELETE_PERSON, "d - usun osobe",      { 68 },     true },
        { SAVE,         "s - zapisz drzewo",    { 83 },     true },
        { LOAD,         "l - odczytaj drzewo",  { 76 },     true },
        { EXIT,         "q - zakoncz program",  { 81, 27 }, true },
        { ARROW_UP,     "",                     { 38 },     false },
        { ARROW_DOWN,   "",                     { 40 },     false },
    };

    int act_line;
    int curr_max_items;
    int skip_lines;

    HANDLE h_stdout;
    HANDLE h_stdin;

    void check_constraints();
};

#endif // GT_MENU_H
