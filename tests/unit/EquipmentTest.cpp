#include <string>

#include "Database.cppm"
#include "Equipment.cppm"
#include "Inspection.cppm"
#include "TestRunner.hpp"

using namespace EquipCheck;

namespace
{
    Equipment makeMotor(std::string id = "MTR-001")
    {
        return Equipment { id, "Production Motor 1", Equipment::Category::ELECTRIC_MOTOR };
    }

    void testEquipmentProperties(TestRunner& tests)
    {
        Equipment equipment = makeMotor();

        EXPECT(tests, equipment.getId() == "MTR-001");
        EXPECT(tests, equipment.getName() == "Production Motor 1");
        EXPECT(tests, equipment.getCategory() == Equipment::Category::ELECTRIC_MOTOR);
        EXPECT(tests, equipment.getCategoryLabel() == "Electric Motor");

        equipment.setName("Backup Motor");
        equipment.setCategory(Equipment::Category::WELDING_TOOL);

        EXPECT(tests, equipment.getName() == "Backup Motor");
        EXPECT(tests, equipment.getCategoryLabel() == "Welding Tool");
    }

    void testInspectionEvaluation(TestRunner& tests)
    {
        const Equipment motor = makeMotor();

        const Inspection withinLimits { motor, 68.5F, 3.2F, 4210 };
        const Inspection highTemperature { motor, 80.0F, 3.2F, 4210 };
        const Inspection highVibration { motor, 68.5F, 5.0F, 4210 };
        const Inspection lowTemperature { motor, 40.0F, 3.2F, 4210 };
        const Inspection highOperatingHours { motor, 68.5F, 3.2F, 10'000 };

        EXPECT(tests, withinLimits.getResult() == Inspection::Result::WITHIN_LIMITS);
        EXPECT(tests, withinLimits.getResultLabel() == "Within Limits");
        EXPECT(tests, highTemperature.getResult() == Inspection::Result::DAMAGED);
        EXPECT(tests, highVibration.getResult() == Inspection::Result::DAMAGED);
        EXPECT(tests, lowTemperature.getResult() == Inspection::Result::MAINTENANCE_NEEDED);
        EXPECT(tests, highOperatingHours.getResult() == Inspection::Result::MAINTENANCE_NEEDED);
    }

    void testDatabaseLookupAndInspectionStorage(TestRunner& tests)
    {
        Database database;
        const Equipment motor = makeMotor();
        const Equipment cutter { "CUT-001", "Cutter", Equipment::Category::CUTTING_TOOL };
        const Inspection inspection { motor, 68.5F, 3.2F, 4210 };

        database.addEquipment(motor);
        database.addEquipment(cutter);
        database.recordInspection(inspection);

        const auto foundMotor = database.getEquipmentById("MTR-001");
        const auto missingEquipment = database.getEquipmentById("MTR-999");
        const auto allEquipment = database.getAllEquipment();
        const auto motorInspections = database.getEquipmentInspections("MTR-001");
        const auto cutterInspections = database.getEquipmentInspections(cutter);

        EXPECT(tests, foundMotor.has_value());
        EXPECT(tests, foundMotor->getName() == "Production Motor 1");
        EXPECT(tests, !missingEquipment.has_value());
        EXPECT(tests, allEquipment.size() == 2);
        EXPECT(tests, motorInspections.size() == 1);
        EXPECT(tests, motorInspections.front().getOperatingHours() == 4210);
        EXPECT(tests, cutterInspections.empty());
    }

    void testEquipmentIdentifiersMustBeUnique(TestRunner& tests)
    {
        Database database;

        database.addEquipment(makeMotor("MTR-001"));
        database.addEquipment(Equipment {
            "MTR-001", "Duplicate Motor", Equipment::Category::ELECTRIC_MOTOR
        });

        // The project requirement says every equipment item has a unique ID.
        EXPECT(tests, database.getAllEquipment().size() == 1);
    }
}

int main()
{
    TestRunner tests;

    testEquipmentProperties(tests);
    testInspectionEvaluation(tests);
    testDatabaseLookupAndInspectionStorage(tests);
    testEquipmentIdentifiersMustBeUnique(tests);

    return tests.result();
}
