#include <iostream>
#include <windows.h>
#include <iomanip>

#include "App.h"

namespace GenTree
{

App::App()
    : done { false }
{
#ifdef _DEBUG_
    randomize();
#endif // __DEBUG
}

const char App::name[] = "Drzewo genealogiczne potomkow.";

void App::intro()
{
    std::cout << name << "\n";
}

//get line from stdin, when error or empty line then returns default string
static std::string get_string(std::string default_s)
{
    char buff[256];

    int out = scanf("%255[^\n]*c", buff);
    fflush(stdin);
    if (out <= 0)
        return default_s;
    return std::string(buff);
}

//string to integer (silencing exeptions)
static int s_to_i(std::string s)
{
    int out;
    try
    {
        out = std::stoi(s);
    }
    catch (const std::invalid_argument&)
    {
        return 0;
    }
    catch (const std::out_of_range&)
    {
        return 0;
    }
    return out;
}
static Person edit_person(const Person &p, std::string label = "Edycja osoby.")
{
    std::cout << label << "\n\n";

    std::cout << "Imie [" << p.first_name << "]:\n";
    std::string ofn = get_string(p.first_name);

    std::cout << "Nazwisko [" << p.last_name << "]:\n";
    std::string oln = get_string(p.last_name);

    std::cout << "Rok urodzenia [" << p.birth_year << "]:\n";
    std::string sby = get_string("0");
    int by = s_to_i(sby);
    if (!by)
    {
        by = p.birth_year;
    }

    std::cout << "Plec (K/M) [" << p.sex << "]:\n";
    std::string sx = get_string(std::string("") + p.sex);

    return Person(ofn, oln, by, sx[0]);
}
static Person input_new_person()
{
    Person p;
    return edit_person(p, "Tworzenie nowej osoby.");
}

static void show_persons_list(std::vector<Person>& l, std::string title)
{
    if(l.size())
    {
        std::cout << title << "\n";
        for(auto i: l)
        {
            std:: cout << " " << i << "\n";
        }
    }
}

void App::show_info(const Node *p)
{
    std::vector<Person> siblings, childrens, grandchildrens;

    intro();
    std::cout << "\n";
    std::cout << p->get_person() << "\n";

    p->get_siblings(siblings);
    show_persons_list(siblings, "\nRodzenstwo:");

    p->get_childrens(childrens);
    show_persons_list(childrens, "\nDzieci:");

    p->get_grandchildrens(grandchildrens);
    show_persons_list(grandchildrens, "\nWnuki:");
}
void App::randomize()
{
    Tree rt = rndtree.get_next_tree();
    tree.swap(rt);
}
void App::load_tree(std::string path)
{
    if (!path.length())
        return;

    Tree n_tree;
    if (n_tree.load_tree(path))
    {
        tree.swap(n_tree);
    };
}

void App::on_exit()
{
    done = true;
}
void App::on_add_person()
{
    console.cls();
    intro();

    Person p = input_new_person();
    tree.add_person(tree.find_node_by_id(menu.get_curr_line()), p);
}
void App::on_edit_person()
{
    console.cls();
    intro();

    auto i = tree.find_node_by_id(menu.get_curr_line());
    if (i)
    {
        auto p = edit_person(i->get_person());
        tree.set_person(i, p);
    }
}
void App::on_delete_person()
{
    tree.remove_node_by_id(menu.get_curr_line());
}
void App::on_show_info()
{
    console.cls();
    auto i = tree.find_node_by_id(menu.get_curr_line());
    if(i)
    {
        show_info(i);
        console.get_key();
    }
}
void App::on_load()
{
    console.cls();
    intro();

    std::cout << "Wczytywanie drzewa z pliku.\n\n";
    std::cout << "Podaj nazwe pliku:\n";
    std::string path = get_string("");
    if (!path.length())
        return;

    Tree n_tree;
    if (n_tree.load_tree(path))
    {
        tree.swap(n_tree);
    };
}
void App::on_save()
{
    if (tree.get_size())
    {
        console.cls();
        intro();
        std::cout << "Zapisywanie drzewa do pliku.\n\n";
        std::cout << "Podaj nazwe pliku:\n";
        std::string path = get_string("");
        if (!path.length())
            return;

        tree.save_tree(path);
    }
}
void App::on_help()
{
    console.cls();

    intro();
    menu.show_help();

    console.get_key();
}
void App::on_version()
{
    console.cls();

    intro();
    std::cout << "\n";
    std::cout << "by Sebastian Kucharczyk, 2019\n\n";
    std::cout << "Ver: 1.1\n\n";
    std::cout << "Build: " __TIME__ " " __DATE__ "\n\n";

    console.get_key();
}
void App::on_new_tree()
{
    tree.remove_node_by_id(0);
}
void App::on_arrow_up()
{
    menu.line_up();
}
void App::on_arrow_down()
{
    menu.line_down();
}
void App::on_arrow_left()
{
    menu.set_curr_line(tree.get_node_id(tree.find_node_by_id(menu.get_curr_line())->get_parent()));
}
void App::on_arrow_right()
{
    auto c = tree.find_node_by_id(menu.get_curr_line())->get_leftmost_child();
    if (c)
        menu.set_curr_line(tree.get_node_id(c));
}
void App::on_page_up()
{
    menu.set_curr_line(menu.get_curr_line() - menu.get_max_lines() + 1);
}
void App::on_page_down()
{
    menu.set_curr_line(menu.get_curr_line() + menu.get_max_lines() - 1);
}
void App::on_randomize()
{
    randomize();
}

void App::run(int argc, char *argv[])
{
    if(argc > 1)
    {
        load_tree(argv[1]); //load file on start (first argument in command line)
    }
    while (!done)
    {
        menu.set_curr_max_lines(tree.get_size());

        console.cls();
        intro();
        menu.show();
        tree.show_tree_indented("", menu.get_curr_line(), menu.get_skip_lines(), menu.get_max_lines(), console);
        std::cout.flush();
        Sleep(50);

        auto opt = menu.get_option(console.get_key());
        while (opt == Menu::NONE)
            opt = menu.get_option(console.get_key());

        if(loop_map.find(opt) != loop_map.end())
        {
            auto f = loop_map.at(opt);
            (this->*f)();
        }
        else
        {
            std::cout << "[ERROR] Nieznana opcja: " << opt;
        }
    }
}

const std::unordered_map<Menu::MENU_ITEMS, loop_func, std::hash<int>> App::loop_map =
{
    {Menu::EXIT, on_exit},
    {Menu::ADD_PERSON, on_add_person},

    {Menu::EDIT_PERSON, on_edit_person},
    {Menu::DELETE_PERSON, on_delete_person},

    {Menu::SHOW_INFO, on_show_info},

    {Menu::LOAD, on_load},
    {Menu::SAVE, on_save},

    {Menu::NEW_TREE, on_new_tree},
    {Menu::ARROW_UP, on_arrow_up},
    {Menu::ARROW_DOWN, on_arrow_down},
    {Menu::ARROW_LEFT, on_arrow_left},
    {Menu::ARROW_RIGHT, on_arrow_right},

    {Menu::PAGE_UP, on_page_up},
    {Menu::PAGE_DOWN, on_page_down},

    {Menu::EXIT, on_exit},

    {Menu::HELP, on_help},
    {Menu::VERSION, on_version},

    {Menu::RND_TREE, on_randomize},
};

void App::msgbox(std::string const &msg, std::string const &title, bool justify) const
{
    std::vector<std::string> tmp{msg};
    return msgbox(tmp, title, justify);
}
void App::msgbox(std::vector<std::string> const &msgs, std::string const &title, bool justify) const
{
    size_t max_len = 0;
    for(auto m: msgs)
    {
        max_len = std::max(max_len, m.length());
    }
    int x = console.get_console_width();
    int y = console.get_console_heigth();

    int start_x = x/2 - max_len/2;
    int start_y = y/2 - msgs.size()/2;

    std::string title_line = " " + title + " ";
    if(justify)
            title_line.insert(0, max_len/2 - title_line.length()/2, '-');

    //border top line
    std::cout.fill('-');
    console.gotoxy(start_x - 2, start_y - 1);
    std::cout << "+-" << std::setw(max_len) << std::left << title_line << "-+";
    std::cout.fill(' ');

    for(size_t i = 0; i<msgs.size(); ++i)
    {
        std::string line{msgs[i]};
        if(justify)
            line.insert(0, max_len/2 - msgs[i].length()/2, ' ');
        console.gotoxy(start_x - 2, start_y + i);
        std::cout << "| ";
        std::cout << std::setw(max_len) << std::left << line;
        std::cout << " |";
    }

    //border bottom line
    std::cout.fill('-');
    console.gotoxy(start_x - 2, start_y + msgs.size());
    std::cout << "+-" << std::setw(max_len) << std::setfill('-') << "" << "-+";
    std::cout.fill(' ');

    console.get_key();
}
}
