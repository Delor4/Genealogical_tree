#ifndef CONSOLE_H
#define CONSOLE_H
#include <windows.h>

class Console
{
    public:
        Console();
        virtual ~Console();

    WORD get_key();
    void gotoxy(short x, short y);
    void cls();
    WORD set_text_attr(WORD attr);

    protected:

    private:

    HANDLE h_stdout;
    HANDLE h_stdin;
};

#endif // CONSOLE_H
