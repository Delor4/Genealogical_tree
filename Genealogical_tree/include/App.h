#ifndef GENTREE_APP_H
#define GENTREE_APP_H

#include "Console.h"
#include "Menu.h"
#include "Tree.h"
#include "RndTree.h"

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
    void randomize();
    void load_tree(std::string path);

    void msgbox(std::string const &msg, std::string const &title = "", bool justify = false) const;
    void msgbox(std::vector<std::string> const &msg, std::string const &title = "", bool justify = false) const;

    void on_exit();
    void on_add_person();
    void on_edit_person();
    void on_delete_person();
    void on_show_info();
    void on_load();
    void on_save();
    void on_version();
    void on_help();
    void on_new_tree();
    void on_arrow_up();
    void on_arrow_down();
    void on_arrow_left();
    void on_arrow_right();
    void on_page_up();
    void on_page_down();
    void on_randomize();

    Console console;
    Menu menu;
    Tree tree;

    bool done;

    RndTree rndtree;

    static const char name[];
};
}
#endif // GENTREE_APP_H
