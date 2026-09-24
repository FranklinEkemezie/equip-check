
#include "App.cppm"

namespace EquipCheck
{

    App::App(
        Ui& ui, MenuHandler& menuHandler, Database& db
    ): 
        ui { ui }, 
        menuHandler { menuHandler }, 
        db { db } 
    { };

    void App::run() const
    {

        
        while (true)
        {

            menuHandler.handleOption(ui.getMenuInput());
        }
    }

}
