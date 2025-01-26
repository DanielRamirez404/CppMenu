#pragma once
#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace CppMenu
{

    class Menu 
    {
        
        struct Function
        {
            std::string name{};
            std::function<void()> function{};
        };

        public:

            Menu (const Menu&) = delete;
            Menu& operator=(const Menu&) = delete; 
            Menu(const std::string& title, const std::vector<Function>& menufunctions, const std::string& exitMessage = "GO BACK");
            
            virtual void run() const = 0;
        
        protected:

            std::string m_title{};
            std::string m_exitMessage{};
            
            std::vector<Function> m_menuFunctions{};
            
            bool isUserQuitting(size_t selectedOption) const;
            bool isQuittingConfirmed() const;
            void printTitle() const;
            void print() const;
  
    };

    class MainMenu : public Menu 
    {
        public:
            MainMenu(const std::string& title, const std::vector<Function>& menufunctions);
    };

    class DisplayOnceMenu : public Menu 
    {
        public:
            DisplayOnceMenu(const std::string& title, const std::vector<Function>& menufunctions);
    };
  
}

