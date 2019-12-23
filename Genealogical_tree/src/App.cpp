#include <iostream>
#include <windows.h>

#ifdef _DEBUG_
#include <vector>
#include <algorithm>
#endif // _DEBUG_

#include "App.h"

namespace GenTree
{

#ifdef _DEBUG_
static void init_tree(Tree& tree);
#endif // _DEBUG_

App::App()
    : done { false }
{
#ifdef _DEBUG_
    init_tree(tree);
#endif // __DEBUG
}

void App::intro()
{
    std::cout << "Drzewo genealogiczne potomkow.\n";
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


void App::run()
{
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

    {Menu::VERSION, on_version},
};

#ifdef _DEBUG_
struct names {
    std::string name;
    int prob;
};
struct lnames {
    std::string m_name;
    std::string f_name;
};
#include "../gen_names.hpp"
#include <stdlib.h>
#include <time.h>

int rnd_fname(int range, int n){
    int out = rand() % range;
    for(int i =1; i< n; i++){
        int x = rand() % range;
        if(x < out) out = x;
    }
    return out;
}
void add_rnd_child(Tree& tree, Node *p)
{
    int end_time = 2019;
    int lsize = lastnames.size();
    int size;
    std::string fname;
    std::string lname;
    char sex;
    int by = p->get_person().birth_year + 17 + (rand() % (35 - 17));
    if(by > end_time){
        return;
    }
    switch(rand()&1){
    case 0:
        size = female_fnames.size();
        fname = female_fnames[rnd_fname(size,5)].name;
        lname = lastnames[rand() % lsize].f_name;
        sex = 'F';
        break;
    case 1:
        size = male_fnames.size();
        fname = male_fnames[rnd_fname(size,5)].name;
        //lname = lastnames[rand() % lsize].m_name;
        lname = p->get_person().last_name;
        if(p->get_person().sex != 'M'){
            //std::cout << "Jest " << lname << '\n';
            auto it = std::find_if(lastnames.begin(), lastnames.end(), [&] (lnames l) { return l.f_name.compare(lname)==0; } );
            lname = (*it).m_name;
        }
        sex = 'M';
    };

    Person p1(fname, lname, by, sex);
    Node *i1 = tree.add_person(p, p1);

    int kids = rand() % 5;
    for(int i = 0; i< kids; i++){
        add_rnd_child(tree, i1);
    }

}
static void init_tree(Tree& tree)
{
    srand (time(NULL));
    int start_time = 1900;
    int end_time = 2019;
    //int sizes[]={female_fnames.size(), male_fnames.size()};
    int lsize = lastnames.size();
    int size;
    std::string fname;
    std::string lname;
    char sex;
    switch(rand()&1){
    case 0:
        size = female_fnames.size();
        fname = female_fnames[rand() % size].name;
        lname = lastnames[rand() % lsize].f_name;
        sex = 'F';
        break;
    case 1:
        size = male_fnames.size();
        fname = male_fnames[rand() % size].name;
        lname = lastnames[rand() % lsize].m_name;
        sex = 'M';

    };
    Person p1(fname, lname, start_time+rand()%5, sex);
    //Person p1("Jan", "Kowalski", 1954, 'M');
    Node *i1 = tree.add_person(nullptr, p1);

    int kids = 1+ rand() % 3;
    for(int i = 0; i< kids; i++){
        add_rnd_child(tree, i1);
    }
    //Sleep(5000);
    return;
    Person p2("Janina", "Kowalska", 1974, 'K');
    Node *i2 = tree.add_person(i1, p2);
    Person p5("Dorota", "Kowalska", 1994, 'K');
    tree.add_person(i2, p5);
    Person p6("Daria", "Kowalska", 1994, 'K');
    tree.add_person(i2, p6);

    Person p3("Jambrozy", "Kowalski", 1977, 'M');
    Node *i3 = tree.add_person(i1, p3);
    Person p4("Grazyna", "Kowalska", 1994, 'K');
    tree.add_person(i3, p4);

}

static void init_tree_old(Tree& tree)
{
    Person p1("Jan", "Kowalski", 1954, 'M');
    Node *i1 = tree.add_person(nullptr, p1);

    Person p2("Janina", "Kowalska", 1974, 'K');
    Node *i2 = tree.add_person(i1, p2);
    Person p5("Dorota", "Kowalska", 1994, 'K');
    tree.add_person(i2, p5);
    Person p6("Daria", "Kowalska", 1994, 'K');
    tree.add_person(i2, p6);

    Person p3("Jambrozy", "Kowalski", 1977, 'M');
    Node *i3 = tree.add_person(i1, p3);
    Person p4("Grazyna", "Kowalska", 1994, 'K');
    tree.add_person(i3, p4);

}
#endif // _DEBUG_
}
