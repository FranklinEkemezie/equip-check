#ifndef __MenuHandler_cppm
#define __MenuHandler_cppm

#include "Database.cppm"
#include "Equipment.cppm"
#include "Inspection.cppm"
#include "Ui.cppm"

namespace EquipCheck
{

    class MenuHandler
    {
        
        public:
            MenuHandler(Ui& ui, Database& db);

            void handleOption(Ui::Option option);


        private:

            std::optional<Equipment> retrieveEquipmentById();

            void handleAddEquipment();
            void handleFindEquipment();
            void handleRecordInspection();
            void handleDisplayInspection();
            void handleDisplayAllEquipment();
            void handleExitApp();

        private:
            Ui& ui;
            Database& db;




    };
}

#endif