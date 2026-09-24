#include <format>
#include <iostream>

#include "Database.cppm"


namespace EquipCheck
{

    void Database::addEquipment(Equipment equipment)
    {
        this->equipment.push_back(equipment);
    }

    std::optional<Equipment> Database::getEquipmentById(std::string_view id) const
    {
        for (const auto& e : equipment)
        {
            if (e.getId() == id) return e;
        }

        return std::nullopt;
    }

    std::vector<Equipment> Database::getAllEquipment() const
    {
        return equipment;
    }

    void Database::recordInspection(Inspection inspection)
    {
        inspections.push_back(inspection);
    }

    std::vector<Inspection> Database::getInspections() const
    {
        return inspections;
    }

    std::vector<Inspection> Database::getEquipmentInspections(std::string_view equipmentId) const
    {

        std::vector<Inspection> result { };

        for (const auto& i : getInspections())
        {
            if (i.getEquipment().getId() == equipmentId)
            {
                result.push_back(i);
            }

        }

        return result;
    }

    std::vector<Inspection> Database::getEquipmentInspections(Equipment equipment) const
    {
        return getEquipmentInspections(equipment.getId());
    }



}



