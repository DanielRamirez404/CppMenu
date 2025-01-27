#pragma once
#include <functional>
#include <string>
#include <vector>

namespace CppMenu
{

    class Menu 
    {

        public:
        
            struct Function
            {
                std::string name{};
                std::function<void()> function{};
            };

            Menu (const Menu&) = delete;
            Menu& operator=(const Menu&) = delete; 
            Menu(const std::string& title, const std::vector<Function>& menuFunctions, const std::string& exitMessage = "GO BACK");
            
            virtual void run() const = 0;
            static void setMaxWidth(std::size_t width);     

        protected:

            static std::size_t s_maxWidth;

            std::string m_title{};
            std::string m_exitMessage{};
            
            std::vector<Function> m_menuFunctions{};
            
            bool isUserQuitting(size_t selectedOption) const;
            bool isQuittingConfirmed() const;
             
            static void print(const std::string& string);
            static void printBreak();
            
            void printTitle() const;
            void display() const;
  
    };

    class MainMenu : public Menu 
    {
        public:
            MainMenu(const std::string& title, const std::vector<Function>& menuFunctions) : Menu(title, menuFunctions) {};
            void run() const;
    };

    class DisplayOnceMenu : public Menu 
    {
        public:
            DisplayOnceMenu(const std::string& title, const std::vector<Function>& menuFunctions);
            void run() const;
    };
  
}

