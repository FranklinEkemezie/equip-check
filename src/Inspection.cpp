#include <iostream>
#include <format>
#include <stdexcept>

#include "Inspection.cppm"

namespace EquipCheck
{

    Inspection::Inspection(
        Equipment equipment,
        float temperature,
        float vibration,
        int operatingHours
    ):
        equipment { equipment },
        temperature { temperature },
        vibration { vibration },
        operatingHours { operatingHours }
    { };

    Inspection::Result Inspection::getResult() const
    {

        if (
            temperature >= TEMPERATURE_LIMITS.second || 
            vibration   >= VIBRATION_LIMITS.second
        ) return Result::DAMAGED;

        if (
            temperature     <= TEMPERATURE_LIMITS.first || 
            vibration       <= VIBRATION_LIMITS.first   || 
            operatingHours  >= OPERATION_HOURS_THRESHOLD
        ) return Result::MAINTENANCE_NEEDED;
        
        return Result::WITHIN_LIMITS;
    }

    std::string Inspection::getResultLabel(Result result) const
    {
        switch (result)
        {
            case Result::WITHIN_LIMITS:         return "Within Limits";
            case Result::MAINTENANCE_NEEDED:    return "Maintenance Needed";
            case Result::DAMAGED:               return "Damaged";
            default: throw std::invalid_argument { "Invalid result" };
        }
    }

    std::string Inspection::getResultLabel() const
    {
        return getResultLabel(getResult());
    }

    Equipment Inspection::getEquipment() const
    {
        return equipment;
    }

    float Inspection::getTemperature() const
    {
        return temperature;
    }

    float Inspection::getVibration() const
    {
        return vibration;
    }
    
    int Inspection::getOperatingHours() const
    {
        return operatingHours;
    }

    void Inspection::printInfo() const
    {

        std::cout << '\n' << std::format(
            "Temperature:       {}°C\n"
            "Vibration:         {}mm/s\n"
            "Operating Time:    {}hrs\n"
            "Inspection Result: {}\n",

            getTemperature(),
            getVibration(),
            getOperatingHours(),
            getResultLabel()
        ) << std::endl;
    }

}