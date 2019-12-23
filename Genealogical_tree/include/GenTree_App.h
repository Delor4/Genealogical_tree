#ifndef GENTREE_APP_H
#define GENTREE_APP_H

#include "Console.h"
#include "GT_Menu.h"
#include "GenTree.h"

class GenTree_App;
typedef void (GenTree_App::*loop_func)();

class GenTree_App
{

    public:
        GenTree_App();
        virtual ~GenTree_App();

        void run();
    protected:
    private:
        void intro() const;
        Person edit_person(const Person &p, std::string label = "Edycja osoby.") const;
        Person input_new_person() const;
        void show_info(const GenTreeItem *p) const;

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
        std::unordered_map<GT_Menu::MENU_ITEMS, loop_func, std::hash<int>> get_main_loop();

        Console console;
        GT_Menu menu;
        GenTree tree;

        bool done;
};

#endif // GENTREE_APP_H
