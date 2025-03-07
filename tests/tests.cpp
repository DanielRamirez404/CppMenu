#include "testfunctions.h"
#include "cppmenu.h"

int main() 
{
    CppMenu::CommonMenu menu
    {
        "THIS IS AN EXAMPLE OF A REALLY LONG MAIN MENU TITLE THAT SHOULDN\'T FIT INSIDE A NORMALLY-SIZED MENU",

        CppMenu::Menu::Items
        { 
            { "print hello world", &printHelloWorld }, 
            { "throw error", &throwError },
            { "Setting ", &showSettings, false }
        },

        true
    };

    menu.run();

    return 0;
}
