#pragma once
#include <cstddef>
#include <functional>
#include <string>
#include <vector>
#include <exception>

namespace CppMenu
{
    void setMaxWidth(std::size_t width);
    void print(const std::string& string);
    void printBreak();
    void centerPrint(const std::string& string);
    void pressEnterToContinue();
    
    class Menu 
    {
        public:
        
            struct Function
            {
                std::string name{};
                std::function<void()> function{};
            };
            
            friend void CppMenu::setMaxWidth(std::size_t width);
            friend void CppMenu::print(const std::string& string);
            friend void CppMenu::printBreak();
            friend void CppMenu::centerPrint(const std::string& string);

            using Items = std::vector<Function>;

        protected:

            Menu(const std::string& title, const Items& items, const std::string& exitMessage);
            Menu (const Menu&) = delete;
            Menu& operator=(const Menu&) = delete; 
            
            virtual void run() const = 0;

            std::size_t getIndexFromUser() const;
            void executeItem(std::size_t index) const;
            bool isQuitting(std::size_t selectedOption) const;
            bool isUserQuitting() const;

        private:

            static std::size_t s_maxWidth;
            
            std::string m_title{};
            std::string m_exitMessage{};
            Items m_items{};
            
            void display() const;
            void printTitle() const;
            void displayWithError(const std::exception& exception, const std::string& message = "An error happened handling your input") const;
            
            template<typename T> T handleInput(std::function<T()> inputHandler) const;
    };
    
    template<typename T> T CppMenu::Menu::handleInput(std::function<T()> inputHandler) const
    {
        display();

        T value{};
        
        while (true)
        {
            try 
            {
                value = inputHandler();
                break;
            }
            catch (const std::exception& exception)
            {
                displayWithError(exception);
            }
        }
        
        return value;
    }

    class CommonMenu : public Menu 
    {
        public:
            CommonMenu(const std::string& title, const Items& items, bool isMainMenu = false);
            void run() const;
    };

    class DisplayOnceMenu : public Menu 
    {
        public:
            DisplayOnceMenu(const std::string& title, const Items& items);
            void run() const;
    };
}

