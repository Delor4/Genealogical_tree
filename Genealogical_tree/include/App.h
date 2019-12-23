#ifndef GENTREE_APP_H
#define GENTREE_APP_H

#include "Console.h"
#include "Menu.h"
#include "Tree.h"

namespace GenTree
{
class App;
typedef void (App::*loop_func)();

class App
{

public:
    App();
    virtual ~App();

    void run();
protected:
private:
    void intro() const;
    Person edit_person(const Person &p, std::string label = "Edycja osoby.") const;
    Person input_new_person() const;
    void show_info(const Item *p) const;

    void on_exit();
    void on_add_person();
    void on_edit_person();
    void on_delete_person();
    void on_show_info();
    void on_load();
    void on_save();
    void on_version();
    void on_new_tree();
    void on_arrow_up();
    void on_arrow_down();
    void on_arrow_left();
    void on_arrow_right();
    void on_page_up();
    void on_page_down();
    const std::unordered_map<Menu::MENU_ITEMS, loop_func, std::hash<int>>& get_main_loop() const;

    Console console;
    Menu menu;
    Tree tree;

    bool done;
};
}
#endif // GENTREE_APP_H
