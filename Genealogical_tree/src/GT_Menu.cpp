#include "GT_Menu.h"

#include <iostream>

GT_Menu::GT_Menu()
    : act_line{ 0 }
    , skip_lines{ 0 }
    , h_stdout{ GetStdHandle(STD_OUTPUT_HANDLE) }
    , h_stdin{ GetStdHandle(STD_INPUT_HANDLE) }
{
}

GT_Menu::~GT_Menu()
{
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
    DWORD events;
    INPUT_RECORD buffer;

    ReadConsoleInput(h_stdin, &buffer, 1, &events);
    if (buffer.Event.KeyEvent.bKeyDown) {
            std::cout << buffer.Event.KeyEvent.wVirtualKeyCode;
        for (auto& i : items) {
            for (auto k : i.short_keys) {
                if (k == buffer.Event.KeyEvent.wVirtualKeyCode)
                    return i.ID;
            }
        }
    }
    return GT_Menu::NONE;
};

void GT_Menu::gotoxy(short x, short y)
{
    COORD coord_screen = { x, y };
    SetConsoleCursorPosition(h_stdout, coord_screen);
}

void GT_Menu::cls(void)
{
    COORD coord_screen = { 0, 0 };
    DWORD chars_written;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD con_size;

    GetConsoleScreenBufferInfo(h_stdout, &csbi);
    con_size = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(h_stdout, (TCHAR)' ', con_size, coord_screen, &chars_written);
    GetConsoleScreenBufferInfo(h_stdout, &csbi);
    FillConsoleOutputAttribute(h_stdout, csbi.wAttributes, con_size, coord_screen, &chars_written);
    SetConsoleCursorPosition(h_stdout, coord_screen);
}

WORD GT_Menu::set_text_attr(WORD attr)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h_stdout, &csbi);
    WORD old_attr = csbi.wAttributes;

    SetConsoleTextAttribute(h_stdout, attr);

    return old_attr;
}

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
