//
// Created by Lea Anthony on 7/1/21.
//

#ifndef TRAYMENUSTORE_DARWIN_H
#define TRAYMENUSTORE_DARWIN_H

#include "traymenu_darwin.h"

typedef struct {

	int dummy;

    // This is our tray menu map
    // It maps tray IDs to TrayMenu*
    struct hashmap_s trayMenuMap;

    // This is our menu item map
    // It maps menu Item IDs to NSMenuItems
    struct hashmap_s menuItemMap;

    const char* contextMenuData;

} TrayMenuStore;

TrayMenuStore* NewTrayMenuStore();

void AddTrayMenuToStore(TrayMenuStore* store, const char* menuJSON);
TrayMenu* UpdateTrayMenuInStore(TrayMenuStore* store, const char* menuJSON);
void ShowTrayMenusInStore(TrayMenuStore* store);
void DeleteTrayMenuStore(TrayMenuStore* store);

void SaveMenuItemInStore(TrayMenuStore* store, const char* menuItemID, id nsmenuitem);

TrayMenu* GetTrayMenuFromStore(TrayMenuStore* store, const char* menuID);
id GetMenuItemFromStore(TrayMenuStore* store, const char* menuItemID);
void UpdateTrayMenuLabelInStore(TrayMenuStore* store, const char* JSON);
const char* GetContextMenuDataFromStore(TrayMenuStore *store);

#endif //TRAYMENUSTORE_DARWIN_H
