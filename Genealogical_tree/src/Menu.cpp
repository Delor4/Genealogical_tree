#include "Menu.h"

#include <iostream>
namespace GenTree
{
Menu::Menu()
    : act_line{ 0 }
    , skip_lines{ 0 }
{
    populate_map();
}

void Menu::populate_map()
{
    for (auto& i : items)
    {
        for (auto k : i.short_keys)
        {
            keys_map[k] = i.ID;
        }
    }
}
void Menu::show() const
{
    bool first = true;
    for (auto& i : items)
    {
        if (i.show)
        {
            if (!first)
                std::cout << ", ";
            std::cout << i.label;
            first = false;
        }
    }
    std::cout << "\n";
}
void Menu::show_help() const
{
    std::cout << "\n";
    for(auto l: help_text)
        std::cout << l << "\n";
}
Menu::MENU_ITEMS Menu::get_option(WORD virtual_key) const
{
    if(keys_map.find(virtual_key) != keys_map.end())
    {
        return keys_map.at(virtual_key);
    }
    return Menu::NONE;
};


void Menu::check_constraints()
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

void Menu::line_down()
{
    ++act_line;
    check_constraints();
}

void Menu::line_up()
{
    --act_line;
    check_constraints();
}

void Menu::set_curr_max_lines(int _m)
{
    curr_max_items = _m;
    check_constraints();
}

int Menu::get_curr_line() const
{
    return act_line;
}

int Menu::get_skip_lines() const
{
    return skip_lines;
}
void Menu::set_curr_line(int line)
{
    act_line = line;
    check_constraints();
}
std::vector<std::string> Menu::get_help() const
{
    return help_text;
}
std::vector<std::string> Menu::help_text{
"F1         - ten tekst",
"n          - usuwa aktualne i tworzy nowe drzewo",
"i / space  - pokazuje informacje o osobie",
"e / enter  - modyfikuje osobe",
"a / ins    - dodaje potomka do aktualnie zaznaczonej osoby",
"d / del    - usuwa osobe",
"s          - zapisuje cale drzewo do pliku",
"l          - odczytuje wczesniej zapisane drzewo",
"F9         - losowe drzewo genealogiczne",
"F2         - informacje o programie",
"q / esc    - wyjscie z programu",
}
;
}

