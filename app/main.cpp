#include <format>
#include <iostream>
#include <stdexcept>

#include "App.cpp"
#include "Database.cppm"
#include "Equipment.cppm"
#include "MenuHandler.cppm"
#include "Ui.cppm"


using namespace EquipCheck;


int main()
{


    Database db { };
    Ui ui { };
    MenuHandler menuHandler { ui, db };
    App app { ui, menuHandler, db };

    app.run();

    return 0;
}