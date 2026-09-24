#ifndef __Inspection_cppm
#define __Inspection_cppm

#include "Equipment.cppm"

namespace EquipCheck
{


    class Inspection
    {

        public:

            enum class Result
            {
                WITHIN_LIMITS,
                MAINTENANCE_NEEDED,
                DAMAGED
            };

            Inspection(
                Equipment equipment,
                float temperature,
                float vibration,
                int operatingHours
            );

            Equipment getEquipment() const;
            float getTemperature() const;
            float getVibration() const;
            int getOperatingHours() const;
            Result getResult() const;
            std::string getResultLabel(Result result) const;
            std::string getResultLabel() const;
            void printInfo() const;


        private:
            Equipment equipment;
            float temperature;
            float vibration;
            int operatingHours;

            const std::pair<int, int> TEMPERATURE_LIMITS { 40, 80 };
            const std::pair<float, float> VIBRATION_LIMITS { 2.0f, 5.0f };
            const int OPERATION_HOURS_THRESHOLD { 10'000 };


    };
}

#endif