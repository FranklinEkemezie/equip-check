#ifndef __Database_cppm
#define __Database_cppm

#include <optional>
#include <vector>

#include "Equipment.cppm"
#include "Inspection.cppm"

namespace EquipCheck
{

    class Database
    {

        public:

            void addEquipment(Equipment equipment);
            std::optional<Equipment> getEquipmentById(std::string_view id) const;
            std::vector<Equipment> getAllEquipment() const;

            void recordInspection(Inspection insepction);
            std::vector<Inspection> getInspections() const;
            std::vector<Inspection> getEquipmentInspections(std::string_view equipmentId) const;
            std::vector<Inspection> getEquipmentInspections(Equipment equipment) const;



        private:
            std::vector<Equipment> equipment { };
            std::vector<Inspection> inspections { };
    };
}


#endif