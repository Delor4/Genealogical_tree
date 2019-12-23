#include "Console.h"

namespace GenTree
{
Console::Console()
    : h_stdout{ GetStdHandle(STD_OUTPUT_HANDLE) }
    , h_stdin{ GetStdHandle(STD_INPUT_HANDLE) }
{
}

Console::~Console()
{
}

WORD Console::get_key()
{
    DWORD events;
    INPUT_RECORD buffer;

    do
    {
        ReadConsoleInput(h_stdin, &buffer, 1, &events);
    }
    while(!buffer.Event.KeyEvent.bKeyDown);

    return buffer.Event.KeyEvent.wVirtualKeyCode;
};
void Console::gotoxy(short x, short y)
{
    COORD coord_screen = { x, y };
    SetConsoleCursorPosition(h_stdout, coord_screen);
}

void Console::cls(void)
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

WORD Console::set_text_attr(WORD attr)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h_stdout, &csbi);
    WORD old_attr = csbi.wAttributes;

    SetConsoleTextAttribute(h_stdout, attr);

    return old_attr;
}
}
