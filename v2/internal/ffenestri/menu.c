//
// Created by Lea Anthony on 18/1/21.
//

#include "menu.h"

Menu* NewMenu(struct JsonNode* menuData, struct JsonNode* radioData, MenuManager* manager) {

    if( menuData == NULL ) return NULL;
    if( manager == NULL ) return NULL;

    Menu *result = NEW(Menu);

    // No label by default
    result->label = STRCOPY(getJSONStringDefault(menuData, "l", ""));

    // Setup platform specific menu data
    SetupMenuPlatformData(result);

    // Init menu item list
    vec_init(&result->menuItems);

    // Get the menu items
    JsonNode* items = getJSONObject(menuData, "i");
    if( items != NULL ) {

        // Process the menu data
        JsonNode *item;
        json_foreach(item, items) {
            const char *ID = mustJSONString(item, "I");
            MenuItem *menuItem = HASHMAP_GET(manager->menuItems, ID);
            if (menuItem == NULL) {
                // Process each menu item
                menuItem = processMenuItem(result, item, manager);

                // Filter out separators
                if (menuItem->ID != NULL) {
                    HASHMAP_PUT(manager->menuItems, menuItem->ID, menuItem);
                }
            }
            AddMenuItemToMenu(result, menuItem, manager);
        }

        if (radioData != NULL) {
            // Iterate radio groups
            JsonNode *radioGroup;
            json_foreach(radioGroup, radioData) {
                // Get item label
                processRadioGroup(result, radioGroup, manager);
            }
        }
    }

    return result;
}

MenuItem* processMenuItem(Menu *menu, JsonNode *item, MenuManager *manager) {


    // Get the role
    const char *role = getJSONString(item, "r");
    if( role != NULL ) {
        // Roles override everything else
//        return NewMenuItemForRole(role, menu, item, manager);
    }

    Menu* submenu = NULL;

    // Check if this is a submenu
//    JsonNode *submenuData = json_find_member(item, "S");
//    if( submenuData != NULL ) {
//        submenu = NewMenu(submenuData)
//        // Get the label
//        JsonNode *menuNameNode = json_find_member(item, "l");
//        const char *name = "";
//        if ( menuNameNode != NULL) {
//            name = menuNameNode->string_;
//        }
//
//        id thisMenuItem = createMenuItemNoAutorelease(str(name), NULL, "");
//        id thisMenu = createMenu(str(name));
//
//        msg(thisMenuItem, s("setSubmenu:"), thisMenu);
//        msg(parentMenu, s("addItem:"), thisMenuItem);
//
//        JsonNode *submenuItems = json_find_member(submenu, "i");
//        // If we have no items, just return
//        if ( submenuItems == NULL ) {
//            return;
//        }
//
//        // Loop over submenu items
//        JsonNode *item;
//        json_foreach(item, submenuItems) {
//            // Get item label
//            processMenuItem(menu, thisMenu, item);
//        }
//
//        return;
//    }


    // Get the ID
    const char *menuItemID = mustJSONString(item, "I");

    // Get the label(s)
    const char* label = getJSONStringDefault(item, "l", "");
    const char* alternateLabel = getJSONString(item, "L");

    bool checked = getJSONBool(item, "c");
    bool hidden = getJSONBool(item, "h");
    bool disabled = getJSONBool(item, "d");
    const char* RGBA = getJSONString(item, "R");
    const char* font = getJSONString(item, "F");
    const char* image = getJSONString(item, "i");

    int fontSize = 0;
    getJSONInt(item, "F", &fontSize);

    // Get the Accelerator
    JsonNode *accelerator = json_find_member(item, "a");
    const char *acceleratorKey = NULL;
    const char **modifiers = NULL;

    // If we have an accelerator
    if( accelerator != NULL ) {
        // Get the key
        acceleratorKey = getJSONString(accelerator, "Key");
        // Check if there are modifiers
        JsonNode *modifiersList = json_find_member(accelerator, "Modifiers");
        if ( modifiersList != NULL ) {
            // Allocate an array of strings
            int noOfModifiers = json_array_length(modifiersList);

            // Do we have any?
            if (noOfModifiers > 0) {
                modifiers = malloc(sizeof(const char *) * (noOfModifiers + 1));
                JsonNode *modifier;
                int count = 0;
                // Iterate the modifiers and save a reference to them in our new array
                json_foreach(modifier, modifiersList) {
                    // Get modifier name
                    modifiers[count] = STRCOPY(modifier->string_);
                    count++;
                }
                // Null terminate the modifier list
                modifiers[count] = NULL;
            }
        }
    }

    // has callback?
    bool hasCallback = getJSONBool(item, "C");

    // Get the Type
    const char *type = mustJSONString(item, "t");

    MenuItem* menuItem;
    enum MenuItemType menuItemType;
    if( STREQ(type, "t")) {
        menuItemType = Text;
    }
    else if ( STREQ(type, "s")) {
        menuItemType = Separator;
    }
    else if ( STREQ(type, "c")) {
        menuItemType = Checkbox;
    }
    else if ( STREQ(type, "r")) {
        menuItemType = Radio;
    } else {
        menuItemType = -1;
        ABORT("Unknown Menu Item type '%s'!", type);
    }
    menuItem = NewMenuItem(menuItemType, menuItemID, label, alternateLabel, disabled, hidden, checked, RGBA, font, fontSize, image, acceleratorKey, modifiers, hasCallback, submenu);
    return menuItem;
}

void DeleteMenu(Menu* menu) {

    // NULL guard
    if( menu == NULL ) return;

    // Delete the platform specific menu data
    DeleteMenuPlatformData(menu);

    // Clean up other data
    MEMFREE(menu->label);

    // Clear the menu items vector
    vec_deinit(&menu->menuItems);
}

const char* MenuAsJSON(Menu* menu) {

    if( menu == NULL ) return NULL;

    JsonNode *jsonObject = json_mkobject();
    JSON_ADD_STRING(jsonObject, "Label", menu->label);
    return json_encode(jsonObject);
}

JsonNode* MenuAsJSONObject(Menu* menu) {

    if( menu == NULL ) return NULL;

    JsonNode *jsonObject = json_mkobject();
    JSON_ADD_STRING(jsonObject, "Label", menu->label);
    if( vec_size(&menu->menuItems) > 0 ) {
        JsonNode* items = json_mkarray();
        int i; MenuItem *menuItem;
        vec_foreach(&menu->menuItems, menuItem, i) {
            JSON_ADD_ELEMENT(items, MenuItemAsJSONObject(menuItem));
        }
        JSON_ADD_OBJECT(jsonObject, "Items", items);
    }
    return jsonObject;
}


void processRadioGroup(Menu *menu, JsonNode *radioGroup, MenuManager* manager) {

    JsonNode *members = json_find_member(radioGroup, "Members");
    JsonNode *member;

    int groupLength = json_array_length(radioGroup);
    // Allocate array
    size_t arrayLength = sizeof(id)*(groupLength+1);
    MenuItem* memberList[arrayLength];

    // Build the radio group items
    int count=0;
    json_foreach(member, members) {
        // Get menu by id
        MenuItem* menuItem = HASHMAP_GET(manager->menuItems, (char*)member->string_);
        // Save Member
        memberList[count] = menuItem;
        count = count + 1;
    }
    // Null terminate array
    memberList[groupLength] = 0;

    // Store the members
    json_foreach(member, members) {
        // Copy the memberList
        char *newMemberList = (char *)malloc(arrayLength);
        memcpy(newMemberList, memberList, arrayLength);
        // add group to each member of group
        HASHMAP_PUT(menu->radioGroups, member->string_, newMemberList);

    }

}

void AddMenuItemToMenu(Menu* menu, MenuItem* menuItem, MenuManager* manager) {
    vec_push(&menu->menuItems, menuItem);
    PlatformAddMenuItemToMenu(menu, menuItem, manager);
}

// Creates a JSON message for the given menuItemID and data
const char* CreateMenuClickedMessage(const char *menuItemID, const char *data) {

    JsonNode *jsonObject = json_mkobject();
    if (menuItemID == NULL ) {
        ABORT("Item ID NULL for menu!!\n");
    }
    json_append_member(jsonObject, "i", json_mkstring(menuItemID));
    if (data != NULL) {
        json_append_member(jsonObject, "data", json_mkstring(data));
    }
    const char *payload = json_encode(jsonObject);
    json_delete(jsonObject);
    const char *result = concat("MC", payload);
    MEMFREE(payload);
    return result;
}