#include <iostream>
#include <windows.h>

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
    cout << "Drzewo genealogiczne.\n";
}

std::string get_string(std::string default_s){
    char buff[256];

    int out = scanf("%255[^\n]*c",buff);
    fflush(stdin);
    if(out <= 0) return default_s;
    return std::string(buff);
}
int s_to_i(std::string s)
{
    int out;
    try{
        out = std::stoi(s);
    } catch (const std::invalid_argument& ) {
        return 0;
    } catch (const std::out_of_range& ) {
        return 0;
    }
    return out;
}
Person input_new_person(){
    intro();
    std::cout << "Tworzenie nowej osoby.\n\n";

    std::cout << "Imie:\n";
    std::string ofn = get_string("John");

    std::cout << "Nazwisko:\n";
    std::string oln = get_string("Doe");

    std::cout << "Rok urodzenia:\n";
    std::string sby = get_string("1900");
    int by = s_to_i(sby);
    if(!by) by=1900;

    std::cout << "Plec (K/M):\n";
    std::string sx = get_string("M");

    return Person(ofn,oln, by, sx[0]);
}

Person edit_person(GenTreeItem *i){
    Person p = i->get_person();
    intro();
    std::cout << "Edycja osoby.\n\n";

    std::cout << "Imie ["<< p.first_name <<"]:\n";
    std::string ofn = get_string(p.first_name);

    std::cout << "Nazwisko ["<< p.last_name <<"]:\n";
    std::string oln = get_string(p.last_name);

    std::cout << "Rok urodzenia ["<< p.birth_year <<"]:\n";
    std::string sby = get_string("0");
    int by = s_to_i(sby);
    if(!by){
        by=p.birth_year;
    }

    std::cout << "Plec (K/M) ["<< p.sex <<"]:\n";
    std::string sx = get_string(std::string("")+p.sex);

    return Person(ofn,oln, by, sx[0]);
}
void save_tree(GenTree &tree)
{
    intro();
    std::cout << "Zapisywanie drzewa do pliku.\n\n";
    std::cout << "Podaj nazwe pliku:\n";
    std::string path = get_string("");
    if(!path.length()) return;

    tree.save(path);
}
int main()
{
    GT_Menu menu;
    GenTree tree;

    init_tree(tree);
    while(true){
        menu.set_curr_max_lines(tree.get_size());
        menu.cls();
        intro();

        menu.show();

        tree.show("", menu.get_curr_line(), menu);
        std::cout.flush();
        Sleep(50);

        auto opt = menu.get_option();
        while(opt == GT_Menu::NONE) opt = menu.get_option();

        switch(opt){
        case GT_Menu::EXIT:
            exit(0);
        case GT_Menu::ADD_PERSON:
            {
                menu.cls();
                Person p = input_new_person();
                tree.add_person(tree.find_by_id(menu.get_curr_line()), p);
            }
            break;
        case GT_Menu::EDIT_PERSON:
            {
                menu.cls();
                GenTreeItem * i = tree.find_by_id(menu.get_curr_line());
                if(!i){
                    //TODO: show error
                }else{
                    Person p = edit_person(i);
                    tree.set_person(i, p);
                }
            }
            break;
        case GT_Menu::DELETE_PERSON:
            tree.remove_by_id(menu.get_curr_line());
            break;
        case GT_Menu::LOAD:
            // TODO:
            break;
        case GT_Menu::SAVE:
            if(tree.get_size()){
                menu.cls();
                save_tree(tree);
            }
            break;
        case GT_Menu::ARROW_DOWN:
            menu.line_down();
            break;
        case GT_Menu::ARROW_UP:
            menu.line_up();
            break;
        default:
            cout << opt;
            break;
        };
    }
    return 0;
}
