#include <iostream>
#include <windows.h>
#include <iomanip>

#include "Console.h"
#include "GT_Menu.h"
#include "GenTree.h"

using namespace std;

void init_tree(GenTree& tree)
{
    Person p1("Jan", "Kowalski", 1954, 'M');
    GenTreeItem *i1 = tree.add_person(nullptr, p1);

        Person p2("Janina", "Kowalska", 1974, 'K');
        GenTreeItem *i2 = tree.add_person(i1, p2);
            Person p5("Dorota", "Kowalska", 1994, 'K');
            tree.add_person(i2, p5);
            Person p6("Daria", "Kowalska", 1994, 'K');
            tree.add_person(i2, p6);

        Person p3("Jambrozy", "Kowalski", 1977, 'M');
        GenTreeItem *i3 = tree.add_person(i1, p3);
            Person p4("Grazyna", "Kowalska", 1994, 'K');
            tree.add_person(i3, p4);

}

void intro()
{
    cout << "Drzewo genealogiczne potomkow.\n";
}

std::string get_string(std::string default_s)
{
    char buff[256];

    int out = scanf("%255[^\n]*c", buff);
    fflush(stdin);
    if (out <= 0)
        return default_s;
    return std::string(buff);
}
int s_to_i(std::string s)
{
    int out;
    try {
        out = std::stoi(s);
    }
    catch (const std::invalid_argument&) {
        return 0;
    }
    catch (const std::out_of_range&) {
        return 0;
    }
    return out;
}

Person edit_person(const Person &p, std::string label = "Edycja osoby.")
{
    intro();
    std::cout << label << "\n\n";

    std::cout << "Imie [" << p.first_name << "]:\n";
    std::string ofn = get_string(p.first_name);

    std::cout << "Nazwisko [" << p.last_name << "]:\n";
    std::string oln = get_string(p.last_name);

    std::cout << "Rok urodzenia [" << p.birth_year << "]:\n";
    std::string sby = get_string("0");
    int by = s_to_i(sby);
    if (!by) {
        by = p.birth_year;
    }

    std::cout << "Plec (K/M) [" << p.sex << "]:\n";
    std::string sx = get_string(std::string("") + p.sex);

    return Person(ofn, oln, by, sx[0]);
}
Person input_new_person()
{
    Person p;
    return edit_person(p, "Tworzenie nowej osoby.");
}

void show_persons_list(std::vector<Person>& l, std::string title){
    if(l.size()){
        std::cout << title << "\n";
        for(auto i: l){
            std:: cout << " " << i << "\n";
        }
    }
}
void show_info(GenTreeItem *p)
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

void on_exit(GenTree &, GT_Menu &, Console &)
{
    exit(0);
}
void on_add_person(GenTree & tree, GT_Menu &menu, Console &console)
{
    console.cls();
    Person p = input_new_person();
    tree.add_person(tree.find_by_id(menu.get_curr_line()), p);
}
void on_edit_person(GenTree & tree, GT_Menu &menu, Console &console)
{
    console.cls();
    auto i = tree.find_by_id(menu.get_curr_line());
    if (i) {
        auto p = edit_person(i->get_person());
        tree.set_person(i, p);
    }
}
void on_delete_person(GenTree & tree, GT_Menu &menu, Console &console)
{
    tree.remove_by_id(menu.get_curr_line());
}
void on_show_info(GenTree & tree, GT_Menu &menu, Console &console)
{
    console.cls();
    auto i = tree.find_by_id(menu.get_curr_line());
    if(i){
        show_info(i);
        console.get_key();
    }
}
void on_load(GenTree & tree, GT_Menu &menu, Console &console)
{
    console.cls();
    intro();

    std::cout << "Wczytywanie drzewa z pliku.\n\n";
    std::cout << "Podaj nazwe pliku:\n";
    std::string path = get_string("");
    if (!path.length())
        return;

    GenTree n_tree;
    if (n_tree.load(path)) {
        tree.swap(n_tree);
    };
}
void on_save(GenTree & tree, GT_Menu &menu, Console &console)
{
    if (tree.get_size()) {
        console.cls();
        intro();
        std::cout << "Zapisywanie drzewa do pliku.\n\n";
        std::cout << "Podaj nazwe pliku:\n";
        std::string path = get_string("");
        if (!path.length())
            return;

        tree.save(path);
    }
}
void on_version(GenTree & tree, GT_Menu &menu, Console &console)
{
    console.cls();

    intro();
    std::cout << "\n";
    std::cout << "by Sebastian Kucharczyk, 2019\n\n";
    std::cout << "Ver: 1.0\n\n";
    std::cout << "Build: " __TIME__ " " __DATE__ "\n\n";

    console.get_key();
}
void on_new_tree(GenTree & tree, GT_Menu &menu, Console &console)
{
    tree.remove_by_id(0);
}
void on_arrow_up(GenTree & tree, GT_Menu &menu, Console &console)
{
    menu.line_up();
}
void on_arrow_down(GenTree & tree, GT_Menu &menu, Console &console)
{
    menu.line_down();
}
void on_arrow_left(GenTree & tree, GT_Menu &menu, Console &console)
{
    menu.set_curr_line(tree.get_id(tree.find_by_id(menu.get_curr_line())->get_parent()));
}
void on_arrow_right(GenTree & tree, GT_Menu &menu, Console &console)
{
    auto c = tree.find_by_id(menu.get_curr_line())->get_leftmost_child();
    if (c)
        menu.set_curr_line(tree.get_id(c));
}
void on_page_up(GenTree & tree, GT_Menu &menu, Console &console)
{
    menu.set_curr_line(menu.get_curr_line() - menu.get_max_lines() + 1);
}
void on_page_down(GenTree & tree, GT_Menu &menu, Console &console)
{
    menu.set_curr_line(menu.get_curr_line() + menu.get_max_lines() - 1);
}

std::unordered_map<GT_Menu::MENU_ITEMS, void (*)(GenTree &, GT_Menu &, Console &), std::hash<int>> get_main_loop()
{
    std::unordered_map<GT_Menu::MENU_ITEMS, void (*)(GenTree &, GT_Menu &, Console &), std::hash<int>> loop_map;

    loop_map[GT_Menu::EXIT] = on_exit;
    loop_map[GT_Menu::ADD_PERSON] = on_add_person;
    loop_map[GT_Menu::EDIT_PERSON] = on_edit_person;
    loop_map[GT_Menu::DELETE_PERSON] = on_delete_person;

    loop_map[GT_Menu::SHOW_INFO] = on_show_info;

    loop_map[GT_Menu::LOAD] = on_load;
    loop_map[GT_Menu::SAVE] = on_save;

    loop_map[GT_Menu::NEW_TREE] = on_new_tree;
    loop_map[GT_Menu::ARROW_UP] = on_arrow_up;
    loop_map[GT_Menu::ARROW_DOWN] = on_arrow_down;
    loop_map[GT_Menu::ARROW_LEFT] = on_arrow_left;
    loop_map[GT_Menu::ARROW_RIGHT] = on_arrow_right;

    loop_map[GT_Menu::PAGE_UP] = on_page_up;
    loop_map[GT_Menu::PAGE_DOWN] = on_page_down;

    loop_map[GT_Menu::EXIT] = on_exit;

    loop_map[GT_Menu::VERSION] = on_version;

    return loop_map;
}
int main()
{
    Console console;
    GT_Menu menu;
    GenTree tree;

#ifdef _DEBUG_
    init_tree(tree);
#endif // __DEBUG

    auto loop = get_main_loop();
    while (true) {
        menu.set_curr_max_lines(tree.get_size());
        console.cls();
        intro();

        menu.show();

        tree.show("", menu.get_curr_line(), menu, console);
        std::cout.flush();
        Sleep(50);

        auto opt = menu.get_option(console.get_key());
        while (opt == GT_Menu::NONE)
            opt = menu.get_option(console.get_key());

        if(loop.find(opt) != loop.end()){
            loop.at(opt)(tree, menu, console);
        } else {
            cout << "[ERROR] Nieznana opcja: " << opt;
        }
    }
    return 0;
}
