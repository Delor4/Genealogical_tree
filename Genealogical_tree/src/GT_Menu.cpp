#include "GT_Menu.h"

#include <iostream>

GT_Menu::GT_Menu()
{

}

GT_Menu::~GT_Menu()
{
    //dtor
}


/** @brief (one liner)
  *
  * (documentation goes here)
  */
void GT_Menu::show()
{
    std::cout << "Menu:\n";
    for(auto &i: items){
        std::cout << i.label << '\n';
    }
}

