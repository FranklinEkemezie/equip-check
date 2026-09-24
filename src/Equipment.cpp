#include <format>
#include <iostream>
#include <stdexcept>


#include "Equipment.cppm"


namespace EquipCheck
{

    Equipment::Equipment(
        std::string_view id, 
        std::string_view name, 
        Category category
    ): 
        id { id }, 
        name { name }, 
        category { category } 
    {

    }

    std::string Equipment::getId() const
    {
        return id;
    }
    
    std::string Equipment::getName() const
    { 
        return name; 
    }

    void Equipment::setName(std::string_view name) 
    { 
        this->name = name; 
    }

    Equipment::Category Equipment::getCategory() const
    { 
        return category; 
    
    }
    
    void Equipment::setCategory(Equipment::Category category) 
    { 
        this->category = category; 
    }

    std::string Equipment::getCategoryLabel() const
    {
        switch (getCategory())
        {
            using enum Category;

            case ELECTRIC_MOTOR:    return "Electric Motor";
            case HAND_TOOL:         return "Hand Tool";
            case CUTTING_TOOL:      return "Cutting Tool";
            case WELDING_TOOL:      return "Welding Tool";
            default: throw std::invalid_argument { "Invalid category" };
        }

    }

    
    void Equipment::printInfo() const
    {

        std::cout << '\n' << std::format(
            "ID:        {}\n"
            "Name:      {}\n"
            "Category:  {}\n",
            
            getId(),
            getName(),
            getCategoryLabel()
        );
    }


}