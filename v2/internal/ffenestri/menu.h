//
// Created by Lea Anthony on 18/1/21.
//

#ifndef MENU_H
#define MENU_H

#include "common.h"

enum MenuItemType {Text = 0, Checkbox = 1, Radio = 2, Separator = 3};
static const char *MenuItemTypeAsString[] = {
        "Text", "Checkbox", "Radio", "Separator",
};

enum MenuType {ApplicationMenuType = 0, ContextMenuType = 1, TrayMenuType = 2};
static const char *MenuTypeAsString[] = {
        "ApplicationMenu", "ContextMenu", "TrayMenu",
};



typedef struct {

    // Menu label
    const char *label;

    // A list of menuItem IDs that make up this menu
    vec_void_t menuItems;

    // The platform specific menu data
    void *platformData;

} Menu;

typedef struct {

    // ID of the tray
    const char *ID;

    // The tray label
    const char *Label;

    // The icon name
    const char *Icon;

    // The menu
    Menu* Menu;

    // Platform specific data
    void* platformData;

} TrayMenu;

typedef struct {

    Menu* menu;

} ApplicationMenu;

typedef struct {

    const char* ID;

    Menu* menu;

} ContextMenu;

typedef struct {

    // This is our menu item map using the menuItem ID as a key
    // map[string]*MenuItem
    struct hashmap_s menuItems;

    // This is our context menu map using the context menu ID as a key
    // map[string]*ContextMenu
    struct hashmap_s contextMenus;

    // This is our tray menu map using the tray menu ID as a key
    // map[string]*TrayMenu
    struct hashmap_s trayMenus;

    // Application Menu
    Menu* applicationMenu;

    // Context menu data
    const char* contextMenuData;

} MenuManager;


typedef struct {
    MenuManager* manager;
    const char *menuItemID;
    enum MenuItemType menuItemType;
} MenuItemCallbackData;

typedef struct {
    const char *ID;
    const char* label;
    const char* alternateLabel;
    bool disabled;
    bool hidden;
    const char* colour;
    const char* font;
    int fontSize;
    const char* image;
    bool checked;

    // Keyboard shortcut
    const char* acceleratorKey;
    const char** modifiers;

    // Type of menuItem
    enum MenuItemType type;

    // Indicates if the menuItem has a callback
    bool hasCallback;

    // The platform specific menu data
    void* platformData;

    // Submenu
    Menu* submenu;

    // Radio group for this item
    vec_void_t radioGroup;

    // Data for handling callbacks
    MenuItemCallbackData *callbackData;

} MenuItem;

// MenuItem
MenuItem* NewMenuItem(enum MenuItemType type, const char* ID, const char* label, const char* alternateLabel, bool disabled, bool hidden, bool checked, const char* colour, const char* font, int fontsize, const char* image, const char* acceleratorKey, const char** modifiers, bool hasCallback, Menu* submenu);
void DeleteMenuItem(MenuItem* menuItem);
JsonNode* MenuItemAsJSONObject(MenuItem* menuItem);

// Menu
Menu* NewMenu(JsonNode* menuData, JsonNode* radioData, MenuManager* menuManager);
void DeleteMenu(Menu* menu);
const char* MenuAsJSON(Menu* menu);
JsonNode* MenuAsJSONObject(Menu* menu);
void AddMenuItemToMenu(Menu* menu, MenuItem* menuItem, MenuManager* manager);
MenuItem* processMenuItem(Menu *menu, JsonNode *item, MenuManager *manager);
void processRadioGroup(Menu *menu, JsonNode *radioGroup, MenuManager* manager);

// Tray
TrayMenu* NewTrayMenu(JsonNode* trayJSON, MenuManager *manager);
void DeleteTrayMenu(TrayMenu *trayMenu);
const char* TrayMenuAsJSON(TrayMenu* menu);

// MenuManager
MenuManager* NewMenuManager();
void DeleteMenuManager(MenuManager* manager);
TrayMenu* AddTrayMenuToManager(MenuManager* manager, const char* trayMenuJSON);
void ShowTrayMenus(MenuManager* manager);

// Callbacks
MenuItemCallbackData* NewMenuItemCallbackData(MenuManager *manager, const char* menuItemID, enum MenuItemType menuItemType);
void DeleteMenuItemCallbackData(MenuItemCallbackData* callbackData);
const char* CreateMenuClickedMessage(const char *menuItemID, const char *data);

// Platform
void SetupMenuPlatformData(Menu* menu);
void DeleteMenuPlatformData(Menu* menu);
void SetupMenuItemPlatformData(MenuItem* menuItem);
void DeleteMenuItemPlatformData(MenuItem* menuItem);
void SetupTrayMenuPlatformData(TrayMenu* menu);
void DeleteTrayMenuPlatformData(TrayMenu* menu);
void PlatformAddMenuItemToMenu(Menu *menu, MenuItem* menuItem, MenuManager* manager);
void PlatformUpdateTrayIcon(TrayMenu *menu);

// Platform specific methods
void UnloadTrayIcons();
void LoadTrayIcons();
void ShowTrayMenu(TrayMenu* trayMenu);

#endif //MENU_H
