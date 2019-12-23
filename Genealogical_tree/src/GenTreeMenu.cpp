#include "GenTreeMenu.h"

#include <iostream>

GenTreeMenu::GenTreeMenu()
    : act_line{ 0 }
    , skip_lines{ 0 }
{
    populate_map();
}

GenTreeMenu::~GenTreeMenu()
{
}
void GenTreeMenu::populate_map()
{
    for (auto& i : items) {
        for (auto k : i.short_keys) {
            keys_map[k] = i.ID;
        }
    }
}
void GenTreeMenu::show() const
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

GenTreeMenu::MENU_ITEMS GenTreeMenu::get_option(WORD virtual_key) const
{
    if(keys_map.find(virtual_key) != keys_map.end()){
        return keys_map.at(virtual_key);
    }
    return GenTreeMenu::NONE;
};


void GenTreeMenu::check_constraints()
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

void GenTreeMenu::line_down()
{
    ++act_line;
    check_constraints();
}

void GenTreeMenu::line_up()
{
    --act_line;
    check_constraints();
}

void GenTreeMenu::set_curr_max_lines(int _m)
{
    curr_max_items = _m;
    check_constraints();
}

int GenTreeMenu::get_curr_line() const
{
    return act_line;
}

int GenTreeMenu::get_skip_lines() const
{
    return skip_lines;
}
void GenTreeMenu::set_curr_line(int line)
{
    act_line = line;
    check_constraints();
}
