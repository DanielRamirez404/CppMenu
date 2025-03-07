#include "cppmenu.h"
#include "cppsafeio.h"
#include <functional>
#include <iostream>
#include <string>
#include <cstddef>
#include <exception>

std::size_t CppMenu::Menu::s_maxWidth = 50;

CppMenu::Menu::Menu(const std::string& title, const Menu::Items& items, bool isMainMenu)
    : m_title{ title }, m_items{ items }, m_exitMessage{ (isMainMenu) ? "Exit" : "Go Back" } {}

void CppMenu::setMaxWidth(std::size_t width)
{
    Menu::s_maxWidth = width;
}

void CppMenu::print(const std::string& string) 
{
    if (string.size() < Menu::s_maxWidth)
        std::cout << string << '\n';
    else 
    {
        print(string.substr(0, Menu::s_maxWidth - 1));
        print(string.substr(Menu::s_maxWidth - 1));
    }
}

void CppMenu::printBreak()
{
    for (std::size_t i{ 0 }; i < Menu::s_maxWidth; ++i)
        std::cout << '-';

    std::cout << '\n';
}

void CppMenu::centerPrint(const std::string& string)
{
    const std::size_t stringSize { string.size() };

    if (stringSize < Menu::s_maxWidth)
    {
        const std::size_t halfWidth{ Menu::s_maxWidth / 2 };
        const std::size_t halfStringSize{ stringSize / 2 };

        for (std::size_t i{ 0 }; i < (halfWidth - halfStringSize); ++i)
            std::cout << ' ';

        std::cout << string << '\n';
    }
    else
    {
        centerPrint(string.substr(0, Menu::s_maxWidth - 1));
        centerPrint(string.substr(Menu::s_maxWidth - 1));
    }
}

void CppMenu::Menu::printTitle() const
{
    printBreak();
    centerPrint(m_title);
    printBreak();
}

void CppMenu::Menu::display() const
{
    CppSafeIO::clearConsole();
    printTitle();
    
    for (std::size_t i{0}; i < m_items.size(); ++i)
        print(std::to_string(i + 1).append(") ").append(m_items[i].name));
        
    print(std::to_string(m_items.size() + 1).append(") ").append(m_exitMessage));
    printBreak();
}

void CppMenu::Menu::displayWithError(const std::exception& exception, const std::string& message) const
{
    display();

    print(message);
    printBreak();
    print(std::string{ "Error: " } + std::string{ exception.what() });
    
    printBreak();
    print("Please, try again");
    printBreak();
}


std::size_t CppMenu::Menu::getIndexFromUser() const
{   
    return handleInput<std::size_t>([&]()
        {
            std::cout << "Input: ";
            std::size_t index{ CppSafeIO::getInput<std::size_t>() };
            
            if (index == 0 || index > m_items.size() + 1 )
                throw std::runtime_error{ "Invalid index" };

            return --index;
        }
    );
}

bool CppMenu::Menu::isUserQuitting() const
{
    return handleInput<bool>([&]()
        {
            std::cout << "Do you want to exit? (y/n): ";
            return CppSafeIO::parseYesNoInput();
        }
    );
}

bool CppMenu::Menu::isQuitting(std::size_t selectedOption) const
{
    return selectedOption == m_items.size();
}

void CppMenu::Menu::executeItem(std::size_t index) const
{
    const Item& item{ m_items[index] };

    try 
    {
        CppSafeIO::clearConsole();
        item.function(); 
    }
    catch (const std::exception& exception)
    {
        displayWithError(exception, "The executed function terminated abruptly");
    }

    if (item.haltOnDone)
        pressEnterToContinue();
}

void CppMenu::pressEnterToContinue()
{
    printBreak();
    centerPrint("Press enter to continue");
    printBreak();
    CppSafeIO::pressEnterToContinue();
}

void CppMenu::CommonMenu::run() const
{
    while (true)
    {
        auto index{ getIndexFromUser() };

        if (isQuitting(index))
            if (isUserQuitting())
                break;
            else
                continue;

        executeItem(index);
    }
}
  
void CppMenu::DisplayOnceMenu::run() const
{
    auto index{ getIndexFromUser() };
    
    if (isQuitting(index))
        return;

    executeItem(index);
}
