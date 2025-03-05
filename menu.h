#pragma once
#include <functional>
#include <string>
#include <vector>
#include <exception>

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
            
            static void setMaxWidth(std::size_t width);

            using Items = std::vector<Function>;

        protected:

            Menu(const std::string& title, const Items& items, const std::string& exitMessage);
            Menu (const Menu&) = delete;
            Menu& operator=(const Menu&) = delete; 
            
            static std::size_t s_maxWidth;

            std::string m_title{};
            std::string m_exitMessage{};
            Items m_items{};
            
            virtual void run() const = 0;

            static void print(const std::string& string);
            static void printBreak();
            static void centerPrint(const std::string& string); 
            
            void printTitle() const;
            void display() const;
            
            bool isQuitting(size_t selectedOption) const;
            bool isUserQuitting() const;
            
            std::size_t getIndexFromUser() const;

        private:

            void displayWithInputError(const std::exception& exception) const;
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
                displayWithInputError(exception);
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

