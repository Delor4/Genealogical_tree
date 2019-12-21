#include "GT_Menu.h"

#include <iostream>

GT_Menu::GT_Menu(Console *c)
    : act_line{ 0 }
    , skip_lines{ 0 }
    , console { c }
{
    populate_map();
}

GT_Menu::~GT_Menu()
{
}
void GT_Menu::populate_map()
{
    for (auto& i : items) {
        for (auto k : i.short_keys) {
            keys_map[k] = i.ID;
        }
    }
}
void GT_Menu::show()
{
    bool first = true;
    for (auto& i : items) {
        if (i.show) {
            if (!first)
                std::cout << ", ";
            std::cout << i.label;
            first = false;
        }
    }
    std::cout << "\n";
}

GT_Menu::MENU_ITEMS GT_Menu::get_option()
{
    WORD key = console->wait_for_any_key();
    if(keys_map.find(key) != keys_map.end()){
        return keys_map.at(key);
    }
    return GT_Menu::NONE;
};


void GT_Menu::check_constraints()
{
    if (act_line >= curr_max_items)
        act_line = curr_max_items - 1;

    if (act_line < 0)
        act_line = 0;

    if (skip_lines > act_line)
        skip_lines = act_line;

    if ((act_line - skip_lines) >= MAXLINES)
        skip_lines = act_line - MAXLINES + 1;
}

void GT_Menu::line_down()
{
    ++act_line;
    check_constraints();
}

void GT_Menu::line_up()
{
    --act_line;
    check_constraints();
}

void GT_Menu::set_curr_max_lines(int _m)
{
    curr_max_items = _m;
    check_constraints();
}

int GT_Menu::get_curr_line()
{
    return act_line;
}

int GT_Menu::get_skip_lines()
{
    return skip_lines;
}
void GT_Menu::set_curr_line(int line)
{
    act_line = line;
    check_constraints();
}
