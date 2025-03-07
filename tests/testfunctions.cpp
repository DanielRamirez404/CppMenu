#include "testfunctions.h"
#include "cppsafeio.h"
#include "cppmenu.h"
#include <stdexcept>

void printHelloWorld()
{
    CppMenu::print("Hello world!");
    CppMenu::printBreak(); 
    CppMenu::print(":)");
}

void throwError()
{
    throw std::runtime_error{"This is an example of a throwable function"};
}

void changeMenuSize()
{
    CppMenu::print("Enter your value (Integer)");
    int size { CppSafeIO::getInput<int>() };
    CppMenu::setMaxWidth(size);
    CppSafeIO::clearConsole();
    CppMenu::printBreak();
    CppMenu::print("Updated successfully");
}

void showSettings()
{
    CppMenu::DisplayOnceMenu
    {
        "SETTINGS",

        CppMenu::Menu::Items
        {
            { "Change menu size", &changeMenuSize }
        }

    }.run();

    CppSafeIO::clearConsole();
}
