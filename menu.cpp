#include "menu.h"
#include "cppsafeio.h"
#include <iostream>
#include <string>
#include <cstddef>
#include <exception>

std::size_t CppMenu::Menu::s_maxWidth = 50;

CppMenu::Menu::Menu(const std::string& title, const Menu::Items& items, const std::string& exitMessage)
    : m_title{ title }, m_items{ items }, m_exitMessage{ exitMessage } {}

CppMenu::CommonMenu::CommonMenu(const std::string& title, const Menu::Items& items, bool isMainMenu) 
    : CppMenu::Menu::Menu(title, items, (isMainMenu) ? "EXIT" : "GO BACK") {}

CppMenu::DisplayOnceMenu::DisplayOnceMenu(const std::string& title, const Menu::Items& items) 
    : CppMenu::Menu::Menu(title, items, "EXIT") {}

void CppMenu::Menu::setMaxWidth(std::size_t width)
{
    s_maxWidth = width;
}

void CppMenu::Menu::print(const std::string& string) 
{
    if (string.size() < s_maxWidth)
        std::cout << string << '\n';
    else 
    {
        print(string.substr(0, s_maxWidth - 1));
        print(string.substr(s_maxWidth - 1));
    }
}

void CppMenu::Menu::printBreak()
{
    for (std::size_t i{ 0 }; i < s_maxWidth; ++i)
        std::cout << '-';

    std::cout << '\n';
}

void CppMenu::Menu::centerPrint(const std::string& string)
{
    const std::size_t stringSize { string.size() };

    if (stringSize < s_maxWidth)
    {
        const std::size_t halfWidth{ s_maxWidth / 2 };
        const std::size_t halfStringSize{ stringSize / 2 };

        for (std::size_t i{ 0 }; i < (halfWidth - halfStringSize); ++i)
            std::cout << ' ';

        std::cout << string << '\n';
    }
    else
    {
        centerPrint(string.substr(0, s_maxWidth - 1));
        centerPrint(string.substr(s_maxWidth - 1));
    }
}

void CppMenu::Menu::printTitle() const
{
    printBreak();
    centerPrint(m_title);
    printBreak();
}

std::size_t CppMenu::Menu::getIndexFromUser() const
{
    std::size_t index{ 0 };

    try 
    {
        std::cout << "Input: ";
        index = CppSafeIO::getInput<std::size_t>();
        
        if (index == 0 || index > m_items.size() + 1 )
            throw std::runtime_error{ "Invalid Index" };
    }
    catch (const std::exception& exception)
    {
        CppSafeIO::clearConsole();
        display();

        print("An error happened handling your input.");
        printBreak();
        print(std::string{ "Error: " } + std::string{ exception.what() });
        
        printBreak();
        print("Please, try again.");
        printBreak();

        return getIndexFromUser();
    }

    return --index;
}

void CppMenu::Menu::display() const
{
    printTitle();
    
    for (std::size_t i{0}; i < m_items.size(); ++i)
        print(std::to_string(i + 1).append(") ").append(m_items[i].name));
        
    print(std::to_string(m_items.size() + 1).append(") ").append(m_exitMessage));
    printBreak();
}

void CppMenu::CommonMenu::run() const
{
    display();
    auto index{ getIndexFromUser() };
}
  
void CppMenu::DisplayOnceMenu::run() const
{
    display();
    auto index{ getIndexFromUser() };
}
