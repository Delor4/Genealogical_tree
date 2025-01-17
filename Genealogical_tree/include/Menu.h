#ifndef GENTREE_MENU_H
#define GENTREE_MENU_H

#include <string>
#include <vector>
#include <windows.h>
#include <unordered_map>

#define CHAR_TO_VCODE(c) ((c) - 'a' + 65)

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
        HELP,
        VERSION,
        RND_TREE,
        GT_ERROR
    };

    Menu();
    virtual ~Menu() = default;

    void show() const;
    void show_help() const;
    std::vector<std::string> get_help() const;

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

    static std::vector<GT_MenuItem> items;

    int act_line;
    int curr_max_items;
    int skip_lines;

    void check_constraints();
    void populate_map();
    std::unordered_map<int, MENU_ITEMS> keys_map;

    static std::vector<std::string> help_text;
};
}
#endif // GENTREE_MENU_H
