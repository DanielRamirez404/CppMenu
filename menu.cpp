#include "menu.h"
#include "cpp-safe-io.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstddef>

std::size_t CppMenu::Menu::s_maxWidth = 50;

CppMenu::Menu::Menu(const std::string& title, const std::vector<Menu::Function>& menuFunctions, const std::string& exitMessage)
    : m_title{ title }, m_menuFunctions{ menuFunctions }, m_exitMessage{ exitMessage } {};

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
        print(string.substr(0, s_maxWidth));
        print(string.substr(s_maxWidth));
    }
}

void CppMenu::Menu::printBreak()
{
    for (std::size_t i{ 0 }; i < s_maxWidth; ++i)
        std::cout << '-';

    std::cout << '\n';
}

void CppMenu::Menu::printTitle() const
{
    const std::size_t halfWidth{ s_maxWidth / 2 };
    const std::size_t titleSize { m_title.size() };
    const std::size_t halfTitleSize{ titleSize / 2 };

    printBreak();

    if (m_title.size() < s_maxWidth)
    {
        for (std::size_t i{ 0 }; i < (halfWidth - halfTitleSize); ++i)
            std::cout << ' ';

        std::cout << m_title << '\n';
    }
    else
        print(m_title);

    printBreak();
}

void CppMenu::Menu::display() const
{
    printTitle();
    
    for (std::size_t i{0}; i < m_menuFunctions.size(); ++i)
        print(std::to_string(i + 1).append(") ").append(m_menuFunctions[i].name));
        
    print(std::to_string(m_menuFunctions.size() + 1).append(") ").append(m_exitMessage));
}

void CppMenu::MainMenu::run() const
{
    display();
}
  
void CppMenu::DisplayOnceMenu::run() const
{
    display();
}
