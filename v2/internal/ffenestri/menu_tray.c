//
// Created by Lea Anthony on 18/1/21.
//

#include "menu.h"

TrayMenu* NewTrayMenu(JsonNode* parsedJSON, MenuManager *manager) {

    // NULL GUARD
    if(parsedJSON == NULL) ABORT("[NewTrayMenu] parsedJSON == NULL");

    // Create new tray menu
    TrayMenu* result = NEW(TrayMenu);

    // Initialise other data
    result->ID = STRCOPY(mustJSONString(parsedJSON, "I"));
    result->Label = STRCOPY(getJSONString(parsedJSON, "l"));
    result->Icon = STRCOPY(getJSONString(parsedJSON, "i"));

    // Process menu
    struct JsonNode* menuJSON = getJSONObject(parsedJSON, "m");
    struct JsonNode* radioJSON = getJSONObject(parsedJSON, "r");
    result->Menu = NewMenu(menuJSON, radioJSON, manager);

    // Setup platform data
    SetupTrayMenuPlatformData(result);

    return result;
}

void DeleteTrayMenu(TrayMenu *trayMenu) {

    // NULL guard
    if( trayMenu == NULL ) return;

    // Free the strings
    MEMFREE(trayMenu->ID);
    MEMFREE(trayMenu->Label);
    MEMFREE(trayMenu->Icon);

    // Delete the menu
    DeleteMenu(trayMenu->Menu);

    // Delete the platform data
    DeleteTrayMenuPlatformData(trayMenu);

    // Free tray menu
    MEMFREE(trayMenu);
}

const char* TrayMenuAsJSON(TrayMenu* menu) {

    JsonNode *jsonObject = json_mkobject();
    JSON_ADD_STRING(jsonObject, "ID", menu->ID);
    JSON_ADD_STRING(jsonObject, "Label", menu->Label);
    JSON_ADD_STRING(jsonObject, "Icon", menu->Icon);
    JSON_ADD_OBJECT(jsonObject, "Menu", MenuAsJSONObject(menu->Menu));
    return json_encode(jsonObject);
}

void UpdateTrayIcon(TrayMenu *trayMenu) {

    // Exit early if NULL
    if( trayMenu->Icon == NULL ) {
        return;
    }

    PlatformUpdateTrayIcon(trayMenu);
}