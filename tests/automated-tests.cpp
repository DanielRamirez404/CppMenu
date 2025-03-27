#include "cppmenu.h"
#include <iostream>
#include <exception>

void foo() {
    return;
} 

int main()
{
    try
    {
        CppMenu::CommonMenu menu
        {
            "SAMPLE TITLE",

            { 
                { "Function Title", &foo, false }
            },

            true
        };

        if (false)
            menu.run(); //not executing so that the building and testing log doesn't get erased in case of running ctest -V
        
        std::cout << "Automated tests passed.\n"
                  << "You can include the cppmenu.h header file and use the CppMenu namespace.\n"
                  << "You can try to run CppMenu-Tests executable to test the library's menus.\n";
    }
    catch (const std::exception& exception)
    {
        std::cerr << "CppMenu library's automated tests failed\n"
                  << "Error: " << exception.what() << '\n';
    
        return 1;
    }

    return 0;
}
