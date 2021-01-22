//
// Created by Lea Anthony on 18/1/21.
//

#include "menu.h"

MenuManager* NewMenuManager() {

    MenuManager* result = malloc(sizeof(MenuManager));

    // Allocate Hashmaps
    HASHMAP_INIT(result->menuItems, 32, "menuItems");
    HASHMAP_INIT(result->contextMenus, 4, "contextMenus");
    HASHMAP_INIT(result->trayMenus, 4, "trayMenus");

    // Initialise other data
    result->applicationMenu = NULL;
    result->contextMenuData = NULL;

    return result;
}

int deleteTrayMenu(void *const context, struct hashmap_element_s *const e) {
    DeleteTrayMenu(e->data);
    return -1; // Remove from hashmap
}

int deleteMenuItem(void *const context, struct hashmap_element_s *const e) {
    DeleteMenuItem(e->data);
    return -1; // Remove from hashmap
}

void DeleteMenuManager(MenuManager* manager) {

    // Iterate hashmaps and delete items
    HASHMAP_ITERATE(manager->trayMenus, deleteTrayMenu, NULL);
    HASHMAP_ITERATE(manager->menuItems, deleteMenuItem, NULL);

    // Delete applicationMenu
    DeleteMenu(manager->applicationMenu);

    // Delete Hashmaps
    HASHMAP_DESTROY(manager->trayMenus);
    HASHMAP_DESTROY(manager->contextMenus);
    HASHMAP_DESTROY(manager->menuItems);

    // Delete context menu data
    MEMFREE(manager->contextMenuData);
}

TrayMenu* AddTrayMenuToManager(MenuManager* manager, const char* trayMenuJSON) {

    // Parse JSON
    struct JsonNode* parsedJSON = mustParseJSON(trayMenuJSON);

    // Get the ID
    const char *ID = mustJSONString(parsedJSON, "I");

    // Check if there is already an entry for this menu
    TrayMenu* existingTrayMenu = HASHMAP_GET(manager->trayMenus, ID);
    if ( existingTrayMenu != NULL ) {
        json_delete(parsedJSON);
        return existingTrayMenu;
    }

    // Create new menu
    TrayMenu* newMenu = NewTrayMenu(parsedJSON, manager);
    HASHMAP_PUT(manager->trayMenus, newMenu->ID, newMenu);

    return newMenu;
}

int showTrayMenu(void *const context, struct hashmap_element_s *const e) {
    ShowTrayMenu(e->data);
    // 0 to retain element, -1 to delete.
    return 0;
}
void ShowTrayMenus(MenuManager* manager) {
    HASHMAP_ITERATE(manager->trayMenus, showTrayMenu, NULL);
}

