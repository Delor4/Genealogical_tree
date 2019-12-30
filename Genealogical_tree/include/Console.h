#ifndef GENTREE_CONSOLE_H
#define GENTREE_CONSOLE_H
#include <windows.h>

namespace GenTree
{
class Console
{
public:
    Console();
    virtual ~Console() = default;

    WORD get_key() const;
    void gotoxy(short x, short y) const;
    int get_console_width() const;
    int get_console_heigth() const;
    void cls();
    WORD set_text_attr(WORD attr);

protected:

private:

    HANDLE h_stdout;
    HANDLE h_stdin;
};
}
#endif // GENTREE_CONSOLE_H
