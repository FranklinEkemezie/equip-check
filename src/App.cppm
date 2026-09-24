#ifndef __App_cppm
#define __App_cppm

#include "Database.cppm"
#include "MenuHandler.cppm"
#include "Ui.cppm"

namespace EquipCheck
{

    class App
    {

        public:
            App(Ui& ui, MenuHandler& menuHandler, Database& db);

            void run() const;


        private:
            Ui& ui;
            MenuHandler& menuHandler;
            Database& db;
    };
    
}

#endif