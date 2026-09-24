#include <format>

#include "Ui.cppm"

namespace EquipCheck
{


    std::string Ui::getInput(std::string_view label) const
    {
        std::string input {  };

        std::cout << std::format("{}: ", label);
        getline(std::cin, input);
        
        return input;
    }

    float Ui::getFloatInput(std::string_view label) const
    {
        float input { };
        std::string buffer { };

        std::cout << std::format("{}: ", label);
        getline(std::cin, buffer);

        std::from_chars(buffer.data(), buffer.data() + buffer.size(), input);

        return input;
    }

    int Ui::getIntInput(std::string_view label) const
    {
        return static_cast<int>(getFloatInput(label));
    }

    Ui::Option Ui::getOption(std::string_view label) const
    {
        return static_cast<Option>(getIntInput(label));
    }

    void Ui::showMenu() const
    {
        printHeading("Menu", 10);
        std::cout << '\n' << MENU_OPTIONS << std::endl;
    }

    Ui::Option Ui::getMenuInput() const
    {

        showMenu();

        unsigned short option {  };

        while (true)
        {

            option = getOption("Choose Option");

            if (option <= MAX_OPTION) return option;

            std::cout << "Invalid option." << std::endl;
        }
    }



    void Ui::showCategoryMenu() const
    {
        std::cout << '\n' << CATEGORY_MENU_OPTIONS << std::endl;
    }

    Equipment::Category Ui::getCategoryInput() const
    {

        showCategoryMenu();

        switch (getOption("Equipment Category"))
        {
            using enum Equipment::Category;

            case 1: return ELECTRIC_MOTOR;
            case 2: return HAND_TOOL;
            case 3: return CUTTING_TOOL;
            case 4: return WELDING_TOOL;
            default: throw new std::invalid_argument { "Invalid category options" };
        }

    }

    void Ui::printHeading(std::string_view heading) const
    {
        printHeading(heading, 20);
    }

    void Ui::printHeading(std::string_view heading, unsigned int width) const
    {
        std::cout 
            << '\n'
            << std::format("{:=^{}}", std::format(" {} ", heading), heading.size() + width)
            << std::endl;
    }

    void Ui::printMessage(std::string_view label, std::string_view message) const
    {
        std::cout << '\n' << std::format("[{}] {}", label, message) << std::endl;
    }

    void Ui::printInfo(std::string_view message) const
    {
        printMessage("INFO", message);
    }

    void Ui::printError(std::string_view message) const
    {
        printMessage("ERROR", message);
    }


}