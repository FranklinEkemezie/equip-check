#ifndef __Ui_cppm
#define __Ui_cppm

#include <iostream>
#include <string>

#include "Equipment.cppm"


namespace EquipCheck
{

    class Ui
    {

        public:

            using Option = unsigned short int;

            std::string getInput(std::string_view label) const;
            float getFloatInput(std::string_view label) const;
            int getIntInput(std::string_view label) const;
            Option getOption(std::string_view label) const;
            
            void showMenu() const;
            Option getMenuInput() const;

            void showCategoryMenu() const;
            Equipment::Category getCategoryInput() const;

            void printHeading(std::string_view heading, unsigned int width) const;
            void printHeading(std::string_view heading) const;
            void printMessage(std::string_view label, std::string_view message) const;
            void printInfo(std::string_view message) const;
            void printError(std::string_view message) const;
        
        private:


            unsigned short int MIN_OPTION { 0 };
            unsigned short int MAX_OPTION { 5 };

            const std::string MENU_OPTIONS 
            {
                "1) Add equipment.\n"
                "2) Find equipment by identifier.\n"
                "3) Record an inspection.\n"
                "4) Display an equipment's inspection information.\n"
                "5) Display a summary of all equipment.\n"
                "0) Exit the application.\n"
            };

            const std::string CATEGORY_MENU_OPTIONS
            {
                "1) Electric Motor\n"
                "2) Hand tool\n"
                "3) Cutting tool\n"
                "4) Welding tool\n"
            };


    };
}

#endif