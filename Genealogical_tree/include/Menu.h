#ifndef GT_MENU_H
#define GT_MENU_H

#include <string>
#include <vector>
#include <windows.h>
#include <unordered_map>

namespace GenTree
{
class Menu
{
public:
    static const int MAXLINES = 24;

    enum MENU_ITEMS
    {
        NONE,
        ADD_PERSON,
        EDIT_PERSON,
        DELETE_PERSON,
        NEW_TREE,
        SHOW_INFO,
        SAVE,
        LOAD,
        EXIT,
        ARROW_UP,
        ARROW_DOWN,
        ARROW_LEFT,
        ARROW_RIGHT,
        PAGE_DOWN,
        PAGE_UP,
        VERSION,
        GT_ERROR
    };

    Menu();
    virtual ~Menu() = default;

    void show() const;

    MENU_ITEMS get_option(WORD virtual_key) const;

    void line_down();
    void line_up();
    void set_curr_max_lines(int);
    int get_curr_line() const;
    void set_curr_line(int line);
    int get_skip_lines() const;
    static int get_max_lines()
    {
        return MAXLINES;
    };
protected:
private:
    struct GT_MenuItem
    {
        MENU_ITEMS ID;
        std::string label;
        std::vector<int> short_keys;
        bool show;
    };
#define CHAR_TO_VCODE(c) ((c) - 'a' + 65)
    std::vector<GT_MenuItem> items =
    {
        {
            ADD_PERSON,   "a/i/e/d - dodaj/pokaz/modyfikuj/usun osobe",
            { CHAR_TO_VCODE('a'), VK_INSERT },      true
        },
        { EDIT_PERSON,  "e - modyfikuj osobe",  { CHAR_TO_VCODE('e'), VK_RETURN },      false },
        { DELETE_PERSON, "d - usun osobe",      { CHAR_TO_VCODE('d'), VK_DELETE },      false },
        {
            SHOW_INFO,    "i - inform. o osobie",
            { CHAR_TO_VCODE('i'), VK_SPACE },       false
        },
        { SAVE,         "s - zapisz drzewo",  { CHAR_TO_VCODE('s') },                 false },
        {
            LOAD,         "l/s - odczytaj/zapisz drzewo",
            { CHAR_TO_VCODE('l') },                 true
        },
        { NEW_TREE,     "n - nowe drzewo",    { CHAR_TO_VCODE('n') },                 true },
        { EXIT,         "q - zakoncz program",{ CHAR_TO_VCODE('q'), VK_ESCAPE },      true },
        { ARROW_UP,     "",                   { VK_UP },                              false },
        { ARROW_DOWN,   "",                   { VK_DOWN },                            false },
        { ARROW_LEFT,   "",                   { VK_LEFT },                            false },
        { ARROW_RIGHT,  "",                   { VK_RIGHT },                           false },
        { PAGE_DOWN,    "",                   { VK_NEXT },                            false },
        { PAGE_UP,      "",                   { VK_PRIOR },                           false },
        { VERSION,      "F1 - about",         { VK_F1 },                              false },
    };

    int act_line;
    int curr_max_items;
    int skip_lines;

    void check_constraints();
    void populate_map();
    std::unordered_map<int, MENU_ITEMS> keys_map;
};
}
#endif // GT_MENU_H
