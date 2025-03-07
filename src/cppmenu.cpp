#include "cppmenu.h"
#include "cppsafeio.h"
#include <functional>
#include <iostream>
#include <string>
#include <cstddef>
#include <exception>

std::size_t CppMenu::Menu::s_maxWidth = 50;

CppMenu::Menu::Menu(const std::string& title, const Menu::Items& items, const std::string& exitMessage)
    : m_title{ title }, m_items{ items }, m_exitMessage{ exitMessage } {}

CppMenu::CommonMenu::CommonMenu(const std::string& title, const Menu::Items& items, bool isMainMenu) 
    : CppMenu::Menu::Menu(title, items, (isMainMenu) ? "Exit" : "Go Back") {}

CppMenu::DisplayOnceMenu::DisplayOnceMenu(const std::string& title, const Menu::Items& items) 
    : CppMenu::Menu::Menu(title, items, "Exit") {}

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
    try 
    {
        CppSafeIO::clearConsole();
        m_items[index].function();
    }
    catch (const std::exception& exception)
    {
        displayWithError(exception, "The executed function terminated abruptly");
    }
}

void CppMenu::Menu::pressEnterToContinue()
{
    printBreak();
    print("Press enter to continue");
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
        pressEnterToContinue();
    }
}
  
void CppMenu::DisplayOnceMenu::run() const
{
    auto index{ getIndexFromUser() };
    
    if (isQuitting(index))
        return;

    executeItem(index);
    pressEnterToContinue();
}
