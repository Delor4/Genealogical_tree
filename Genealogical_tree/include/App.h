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
    static const std::unordered_map<Menu::MENU_ITEMS, loop_func, std::hash<int>> loop_map;

    App();
    virtual ~App() = default;

    void run(int argc, char *argv[]);
protected:
private:
    static void intro();
    static void show_info(const Node *p);
    void load_tree(std::string path);

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

    Console console;
    Menu menu;
    Tree tree;

    bool done;
};
}
#endif // GENTREE_APP_H
