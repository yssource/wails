//
// Created by Lea Anthony on 18/1/21.
//

#include "menu.h"

MenuItem* NewMenuItem(enum MenuItemType type, const char* ID, const char* label, const char* alternateLabel, bool disabled, bool hidden, bool checked, const char* colour, const char* font, int fontsize, const char* image, const char* acceleratorKey, const char** modifiers, bool hasCallback, Menu* submenu) {

    MenuItem *result = NEW(MenuItem);

    // Setup
    result->ID = STRCOPY(ID);
    result->label = STRCOPY(label);
    result->alternateLabel = STRCOPY(alternateLabel);
    result->disabled = disabled;
    result->hidden = hidden;
    result->colour = STRCOPY(colour);
    result->font = STRCOPY(font);
    result->fontSize = fontsize;
    result->image = STRCOPY(image);
    result->acceleratorKey = STRCOPY(acceleratorKey);
    result->modifiers = modifiers;
    result->hasCallback = hasCallback;
    result->type = type;
    result->checked = checked;
    result->submenu = submenu;

    result->callbackData = NULL;

    vec_init(&result->radioGroup);

    SetupMenuItemPlatformData(result);

    return result;
}

void DeleteMenuItem(MenuItem* menuItem) {

    MEMFREE(menuItem->ID);
    MEMFREE(menuItem->label);
    MEMFREE(menuItem->alternateLabel);
    MEMFREE(menuItem->colour);
    MEMFREE(menuItem->font);
    MEMFREE(menuItem->image);
    MEMFREE(menuItem->acceleratorKey);

    // Iterate the modifiers and free elements
    if( menuItem->modifiers != NULL ) {
        int i = 0;
        const char *nextItem = menuItem->modifiers[0];
        while (nextItem != NULL) {
            MEMFREE(nextItem);
            i++;
            nextItem = menuItem->modifiers[i];
        }
        MEMFREE(menuItem->modifiers);
    }

    DeleteMenuItemCallbackData(menuItem->callbackData);

    DeleteMenuItemPlatformData(menuItem);

    MEMFREE(menuItem);
}

JsonNode* MenuItemAsJSONObject(MenuItem* menuItem) {

    JsonNode* result = json_mkobject();
    JSON_ADD_STRING(result, "ID", menuItem->ID);
    JSON_ADD_STRING(result, "label", menuItem->label);
    JSON_ADD_STRING(result, "alternateLabel", menuItem->alternateLabel);
    JSON_ADD_BOOL(result, "disabled", menuItem->disabled);
    JSON_ADD_BOOL(result, "hidden", menuItem->hidden);
    JSON_ADD_STRING(result, "colour", menuItem->colour);
    JSON_ADD_STRING(result, "font", menuItem->font);
    JSON_ADD_NUMBER(result, "fontsize", menuItem->fontSize);
    JSON_ADD_STRING(result, "image", menuItem->image);
    JSON_ADD_STRING(result, "acceleratorKey", menuItem->acceleratorKey);
    JSON_ADD_BOOL(result, "hasCallback", menuItem->hasCallback);
    JSON_ADD_STRING(result, "type", MenuItemTypeAsString[menuItem->type]);
    JSON_ADD_BOOL(result, "checked", menuItem->checked);
    return result;
}

MenuItemCallbackData* NewMenuItemCallbackData(MenuManager *manager, const char* menuItemID, enum MenuItemType menuItemType) {
    MenuItemCallbackData* result = NEW(MenuItemCallbackData);

    result->manager = manager;
    result->menuItemID = STRCOPY(menuItemID);
    result->menuItemType = menuItemType;

    return result;
}

void DeleteMenuItemCallbackData(MenuItemCallbackData* callbackData) {

    if( callbackData == NULL ) return;

    MEMFREE(callbackData->menuItemID);
    MEMFREE(callbackData);
}
