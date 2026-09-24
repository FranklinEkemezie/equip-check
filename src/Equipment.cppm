#ifndef __Equipment_cppm
#define __Equipment_cppm

#include <string>
#include <string_view>


namespace EquipCheck
{

    
        class Equipment
        {

            public:

                enum class Category
                {
                    ELECTRIC_MOTOR,
                    HAND_TOOL,
                    CUTTING_TOOL,
                    WELDING_TOOL,
                };


                Equipment(
                    std::string_view id,
                    std::string_view name,
                    Category category
                );

                std::string getId() const;

                std::string getName() const;
                void setName(std::string_view name);

                Category getCategory() const;
                void setCategory(Category category);
                std::string getCategoryLabel() const;

                void printInfo() const;


            private:

                std::string id;
                std::string name;
                Category category;

        };

        
}

#endif