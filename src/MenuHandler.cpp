#include <iostream>
#include <format>

#include "MenuHandler.cppm"

namespace EquipCheck
{

    MenuHandler::MenuHandler(Ui& ui, Database& db): 
        ui { ui }, db { db } { };


    void MenuHandler::handleOption(Ui::Option option)
    {

        switch (option)
        {
            case 1: return handleAddEquipment();
            case 2: return handleFindEquipment();
            case 3: return handleRecordInspection();
            case 4: return handleDisplayInspection();
            case 5: return handleDisplayAllEquipment();
            case 0: return handleExitApp();
            default:
                throw new std::invalid_argument {  
                    std::format("Invalid option: {}", option)
                };
        }
    }

    void MenuHandler::handleAddEquipment()
    {
        ui.printHeading("Enter equipment details");

        Equipment equipment {
            ui.getInput("Equipment ID"),
            ui.getInput("Equipment Name"),
            ui.getCategoryInput()
        };

        db.addEquipment(equipment);

        ui.printInfo(
            std::format("Equipment [ID: {}, Name: {}] added successfully under '{}'",
                equipment.getId(), 
                equipment.getName(), 
                equipment.getCategoryLabel()
            ));
    }

    std::optional<Equipment> MenuHandler::retrieveEquipmentById()
    {
        ui.printHeading("Enter equipment identifier");

        std::string equipmentId { ui.getInput("Equipment ID") };

        auto result { db.getEquipmentById(equipmentId) };

        if (! result.has_value())
        {
            ui.printError(
                std::format("No equipment with ID [{}] found", equipmentId));

            return std::nullopt;
        }

        return result;
    }

    void MenuHandler::handleFindEquipment()
    {

        auto result { retrieveEquipmentById() };

        if (! result.has_value()) return;

        auto equipment { result.value() };
        
        ui.printInfo(std::format("Equipment with ID [{}] found!", equipment.getId()));
        equipment.printInfo();
    }

    void MenuHandler::handleRecordInspection()
    {

        auto result { retrieveEquipmentById() };

        if (! result.has_value()) return;

        auto equipment { result.value() };

        Inspection inspection {
            equipment,
            ui.getFloatInput("Temperature (°C)"),
            ui.getFloatInput("Vibration (mm/s)"),
            ui.getIntInput("Operating Hours")
        };

        db.recordInspection(inspection);

        ui.printInfo("Inspection recorded successfully.");
        ui.printInfo(std::format(
            "Inspection result: {}", inspection.getResultLabel(inspection.getResult())
        ));

    }

    void MenuHandler::handleDisplayInspection()
    {

        auto result { retrieveEquipmentById() };

        if (! result.has_value()) return;

        auto equipment { result.value() };

        equipment.printInfo();

        auto inspections { db.getEquipmentInspections(equipment) };

        if (inspections.empty())
        {
            ui.printError(std::format(
                "No inspections recorded for equipment [{}]", equipment.getId()));

            return;
        }

        std::cout << std::endl;
        for (const auto& i : inspections) i.printInfo();

    }

    void MenuHandler::handleDisplayAllEquipment()
    {
        for (const Equipment& e : db.getAllEquipment()) e.printInfo();
    }

    void MenuHandler::handleExitApp()
    {
        ui.printInfo("Exiting application. Bye!");

        exit(EXIT_SUCCESS);
    }


}