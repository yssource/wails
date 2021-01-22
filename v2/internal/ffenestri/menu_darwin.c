//
// Created by Lea Anthony on 18/1/21.
//

#include "ffenestri.h"
#include "ffenestri_darwin.h"
#include "menu_darwin.h"
#include "menu.h"
#include "trayicons.h"

// A cache for all our tray menu icons
// Global because it's a singleton
struct hashmap_s trayIconCache;

void SetupMenuPlatformData(Menu* menu) {
    MacMenu* result = NEW(MacMenu);
    result->Menu = ALLOC("NSMenu");
    msg(result->Menu, s("initWithTitle:"), str(menu->label));
    msg(result->Menu, s("setAutoenablesItems:"), NO);
    menu->platformData = (void*)result;
}

void DeleteMenuPlatformData(Menu* menu) {

    // Return if null
    if( menu == NULL || menu->platformData == NULL) return;

    MacMenu* macMenu = (MacMenu*) menu->platformData;
    RELEASE(macMenu->Menu);
    macMenu->Menu = NULL;
}


id processAcceleratorKey(const char *key) {

    // Guard against no accelerator key
    if( key == NULL ) {
        return str("");
    }

    if( STREQ(key, "Backspace") ) {
        return strunicode(0x0008);
    }
    if( STREQ(key, "Tab") ) {
        return strunicode(0x0009);
    }
    if( STREQ(key, "Return") ) {
        return strunicode(0x000d);
    }
    if( STREQ(key, "Escape") ) {
        return strunicode(0x001b);
    }
    if( STREQ(key, "Left") ) {
        return strunicode(0x001c);
    }
    if( STREQ(key, "Right") ) {
        return strunicode(0x001d);
    }
    if( STREQ(key, "Up") ) {
        return strunicode(0x001e);
    }
    if( STREQ(key, "Down") ) {
        return strunicode(0x001f);
    }
    if( STREQ(key, "Space") ) {
        return strunicode(0x0020);
    }
    if( STREQ(key, "Delete") ) {
        return strunicode(0x007f);
    }
    if( STREQ(key, "Home") ) {
        return strunicode(0x2196);
    }
    if( STREQ(key, "End") ) {
        return strunicode(0x2198);
    }
    if( STREQ(key, "Page Up") ) {
        return strunicode(0x21de);
    }
    if( STREQ(key, "Page Down") ) {
        return strunicode(0x21df);
    }
    if( STREQ(key, "F1") ) {
        return strunicode(0xf704);
    }
    if( STREQ(key, "F2") ) {
        return strunicode(0xf705);
    }
    if( STREQ(key, "F3") ) {
        return strunicode(0xf706);
    }
    if( STREQ(key, "F4") ) {
        return strunicode(0xf707);
    }
    if( STREQ(key, "F5") ) {
        return strunicode(0xf708);
    }
    if( STREQ(key, "F6") ) {
        return strunicode(0xf709);
    }
    if( STREQ(key, "F7") ) {
        return strunicode(0xf70a);
    }
    if( STREQ(key, "F8") ) {
        return strunicode(0xf70b);
    }
    if( STREQ(key, "F9") ) {
        return strunicode(0xf70c);
    }
    if( STREQ(key, "F10") ) {
        return strunicode(0xf70d);
    }
    if( STREQ(key, "F11") ) {
        return strunicode(0xf70e);
    }
    if( STREQ(key, "F12") ) {
        return strunicode(0xf70f);
    }
    if( STREQ(key, "F13") ) {
        return strunicode(0xf710);
    }
    if( STREQ(key, "F14") ) {
        return strunicode(0xf711);
    }
    if( STREQ(key, "F15") ) {
        return strunicode(0xf712);
    }
    if( STREQ(key, "F16") ) {
        return strunicode(0xf713);
    }
    if( STREQ(key, "F17") ) {
        return strunicode(0xf714);
    }
    if( STREQ(key, "F18") ) {
        return strunicode(0xf715);
    }
    if( STREQ(key, "F19") ) {
        return strunicode(0xf716);
    }
    if( STREQ(key, "F20") ) {
        return strunicode(0xf717);
    }
    if( STREQ(key, "F21") ) {
        return strunicode(0xf718);
    }
    if( STREQ(key, "F22") ) {
        return strunicode(0xf719);
    }
    if( STREQ(key, "F23") ) {
        return strunicode(0xf71a);
    }
    if( STREQ(key, "F24") ) {
        return strunicode(0xf71b);
    }
    if( STREQ(key, "F25") ) {
        return strunicode(0xf71c);
    }
    if( STREQ(key, "F26") ) {
        return strunicode(0xf71d);
    }
    if( STREQ(key, "F27") ) {
        return strunicode(0xf71e);
    }
    if( STREQ(key, "F28") ) {
        return strunicode(0xf71f);
    }
    if( STREQ(key, "F29") ) {
        return strunicode(0xf720);
    }
    if( STREQ(key, "F30") ) {
        return strunicode(0xf721);
    }
    if( STREQ(key, "F31") ) {
        return strunicode(0xf722);
    }
    if( STREQ(key, "F32") ) {
        return strunicode(0xf723);
    }
    if( STREQ(key, "F33") ) {
        return strunicode(0xf724);
    }
    if( STREQ(key, "F34") ) {
        return strunicode(0xf725);
    }
    if( STREQ(key, "F35") ) {
        return strunicode(0xf726);
    }
//  if( STREQ(key, "Insert") ) {
//	return strunicode(0xf727);
//  }
//  if( STREQ(key, "PrintScreen") ) {
//	return strunicode(0xf72e);
//  }
//  if( STREQ(key, "ScrollLock") ) {
//	return strunicode(0xf72f);
//  }
    if( STREQ(key, "NumLock") ) {
        return strunicode(0xf739);
    }

    return str(key);
}

// This converts a string array of modifiers into the
// equivalent MacOS Modifier Flags
unsigned long parseModifiers(const char **modifiers) {

    // Our result is a modifier flag list
    unsigned long result = 0;

    const char *thisModifier = modifiers[0];
    int count = 0;
    while( thisModifier != NULL ) {
        // Determine flags
        if( STREQ(thisModifier, "CmdOrCtrl") ) {
            result |= NSEventModifierFlagCommand;
        }
        if( STREQ(thisModifier, "OptionOrAlt") ) {
            result |= NSEventModifierFlagOption;
        }
        if( STREQ(thisModifier, "Shift") ) {
            result |= NSEventModifierFlagShift;
        }
        if( STREQ(thisModifier, "Super") ) {
            result |= NSEventModifierFlagCommand;
        }
        if( STREQ(thisModifier, "Control") ) {
            result |= NSEventModifierFlagControl;
        }
        count++;
        thisModifier = modifiers[count];
    }
    return result;
}



void SetupMenuItemPlatformData(MenuItem* menuItem) {

    // Create the platform data
    MacMenuItem *macMenuItem = NEW(MacMenuItem);

    menuItem->platformData = macMenuItem;

    // Create the NSMenuItem
    id item = ALLOC("NSMenuItem");
    macMenuItem->MenuItem = item;

//    // TODO: Process ROLE
//    if( menuItem->role != NULL ) {
//
//    }

    id key = processAcceleratorKey(menuItem->acceleratorKey);
    msg(item, s("initWithTitle:action:keyEquivalent:"), str(menuItem->label),
        s("menuItemCallback:"), key);

    msg(item, s("setEnabled:"), !menuItem->disabled);
    msg(item, s("autorelease"));

    // Process modifiers
    if( menuItem->modifiers != NULL ) {
        unsigned long modifierFlags = parseModifiers(menuItem->modifiers);
        msg(item, s("setKeyEquivalentModifierMask:"), modifierFlags);
        menuItem->modifiers = NULL;
    }

}

void DeleteMenuItemPlatformData(MenuItem* menuItem) {

    if( menuItem == NULL || menuItem->platformData == NULL) return;

    MacMenuItem* macMenuItem = (MacMenuItem*) menuItem->platformData;
    RELEASE(macMenuItem->MenuItem);

    MEMFREE(macMenuItem);

}

void PlatformAddMenuItemToMenu(Menu *menu, MenuItem* menuItem, MenuManager* manager) {

    // Return if null
    if( menu == NULL || menu->platformData == NULL) return;
    if( menuItem == NULL || menuItem->platformData == NULL) return;

    // Don't add if the item is hidden
    if( menuItem->hidden ) return;

    // Setup callback
    if( menuItem->hasCallback ) {
        // Create a MenuItemCallbackData
        MacMenuItem* macMenuItem = (MacMenuItem*) menuItem->platformData;
        menuItem->callbackData = NewMenuItemCallbackData(manager, menuItem->ID, Text);

        id wrappedId = msg(c("NSValue"), s("valueWithPointer:"), menuItem->callbackData);
        msg(macMenuItem->MenuItem, s("setRepresentedObject:"), wrappedId);
    }

    MacMenu* macMenu = (MacMenu*) menu->platformData;
    MacMenuItem* macMenuItem = (MacMenuItem*) menuItem->platformData;

    msg(macMenu->Menu, s("addItem:"), macMenuItem->MenuItem);

}

void SetupTrayMenuPlatformData(TrayMenu* menu) {
    MacTrayMenu* result = NEW(MacTrayMenu);
    result->statusBarItem = NULL;

    // TODO: Work out how to make this customisable
    result->iconPosition = NSImageLeft;

    menu->platformData = (void*)result;
}

void DeleteTrayMenuPlatformData(TrayMenu* menu) {

    // Return if null
    if( menu == NULL || menu->platformData == NULL) return;

    MacTrayMenu* macMenu = (MacTrayMenu*) menu->platformData;
    RELEASE(macMenu->statusBarItem);
    macMenu->statusBarItem = NULL;
}


void PlatformUpdateTrayIcon(TrayMenu* trayMenu) {

    MacTrayMenu* macTrayMenu = (MacTrayMenu*) trayMenu->platformData;

    id statusBarButton = msg(macTrayMenu->statusBarItem, s("button"));

    // Empty icon means remove it
    if (trayMenu->Icon == NULL || strlen(trayMenu->Icon) == 0) {
        msg(statusBarButton, s("setImage:"), NULL);
        return;
    }

    id trayImage = HASHMAP_GET(trayIconCache, trayMenu->Icon);
    msg(statusBarButton, s("setImagePosition:"), macTrayMenu->iconPosition);
    msg(statusBarButton, s("setImage:"), trayImage);
}

void UpdateTrayLabel(TrayMenu *trayMenu, const char *label) {

    // Exit early if NULL
    if( trayMenu->Label == NULL ) return;

    // Update button label
    MacTrayMenu* macTrayMenu = (MacTrayMenu*) trayMenu->platformData;
    id statusBarButton = msg(macTrayMenu->statusBarItem, s("button"));
    msg(statusBarButton, s("setTitle:"), str(label));
}

void ShowTrayMenu(TrayMenu* trayMenu) {

    if( trayMenu == NULL || trayMenu->platformData == NULL ) return;

    MacTrayMenu* macTrayMenu = (MacTrayMenu*) trayMenu->platformData;

    // Create a status bar item if we don't have one
    if( macTrayMenu->statusBarItem == NULL ) {
        id statusBar = msg( c("NSStatusBar"), s("systemStatusBar") );
        macTrayMenu->statusBarItem = msg(statusBar, s("statusItemWithLength:"), NSVariableStatusItemLength);
        msg(macTrayMenu->statusBarItem, s("retain"));
    }

    id statusBarButton = msg(macTrayMenu->statusBarItem, s("button"));
    msg(statusBarButton, s("setImagePosition:"), macTrayMenu->iconPosition);

    // Update the icon if needed
    PlatformUpdateTrayIcon(trayMenu);

    // Update the label if needed
    UpdateTrayLabel(trayMenu, trayMenu->Label);

    // If we don't have a menu, return
    if( trayMenu->Menu == NULL ) return;

    // Update the menu
    MacMenu* macMenu = (MacMenu*) trayMenu->Menu->platformData;
    msg(macTrayMenu->statusBarItem, s("setMenu:"), macMenu->Menu);
}

void LoadTrayIcons() {

    // Allocate the Tray Icons
    if( 0 != hashmap_create((const unsigned)4, &trayIconCache)) {
        // Couldn't allocate map
        ABORT("Not enough memory to allocate trayIconCache!");
    }

    unsigned int count = 0;
    while( 1 ) {
        const unsigned char *name = trayIcons[count++];
        if( name == 0x00 ) {
            break;
        }
        const unsigned char *lengthAsString = trayIcons[count++];
        if( name == 0x00 ) {
            break;
        }
        const unsigned char *data = trayIcons[count++];
        if( data == 0x00 ) {
            break;
        }
        char *c;
        unsigned long length = strtol((const char *)lengthAsString, &c, 10);

        // Create the icon and add to the hashmap
        id imageData = msg(c("NSData"), s("dataWithBytes:length:"), data, length);
        id trayImage = ALLOC("NSImage");
        msg(trayImage, s("initWithData:"), imageData);
        HASHMAP_PUT(trayIconCache, (const char *)name, trayImage);
    }
}

void UnloadTrayIcons() {
    // Release the tray cache images
    HASHMAP_ITERATE(trayIconCache, releaseNSObject, NULL);
    HASHMAP_DESTROY(trayIconCache);
}
//
//// Callback for text menu items
//void menuItemCallback(id self, SEL cmd, id sender) {
//    MenuItemCallbackData *callbackData = (MenuItemCallbackData *)msg(msg(sender, s("representedObject")), s("pointerValue"));
//    if( callbackData == NULL) {
//        return;
//    }
//
//    struct TrayMenuStore *store = callbackData->store;
//    const char* menuItemID = callbackData->menuItemID;
//    id nsmenu = GetMenuItemFromStore((TrayMenuStore *) store, menuItemID);
//    if ( nsmenu == NULL ) {
//        // The menu has been deleted!
//        return;
//    }
//
//    const char *message;
//
//    // Update checkbox / radio item
//    if( callbackData->menuItemType == Checkbox) {
//        // Toggle state
//        bool state = msg(nsmenu, s("state"));
//        msg(nsmenu, s("setState:"), (state? NSControlStateValueOff : NSControlStateValueOn));
//    } else if( callbackData->menuItemType == Radio ) {
//        // Check the menu items' current state
//        bool selected = msg(nsmenu, s("state"));
//
//        // If it's already selected, exit early
//        if (selected) return;
//
//        // Get this item's radio group members and turn them off
//        id *members = (id*)hashmap_get(&(callbackData->menu->radioGroupMap), (char*)callbackData->menuItemID, strlen(callbackData->menuItemID));
//
//        // Uncheck all members of the group
//        id thisMember = members[0];
//        int count = 0;
//        while(thisMember != NULL) {
//            msg(thisMember, s("setState:"), NSControlStateValueOff);
//            count = count + 1;
//            thisMember = members[count];
//        }
//
//        // check the selected menu item
//        msg(nsmenu, s("setState:"), NSControlStateValueOn);
//    }
//
//    message = createMenuClickedMessage(menuItemID, GetContextMenuDataFromStore((TrayMenuStore *) store));
//
//    // Notify the backend
//    messageFromWindowCallback(message);
//    MEMFREE(message);
//}

void PlatformMenuItemCallback(id self, SEL cmd, id sender) {
    MenuItemCallbackData *callbackData = (MenuItemCallbackData *)msg(msg(sender, s("representedObject")), s("pointerValue"));
    const char *message;

    MenuManager* manager = callbackData->manager;
    MenuItem* menuItem = HASHMAP_GET(manager->menuItems, callbackData->menuItemID);

    if( menuItem == NULL ) return;

    MacMenuItem *macMenuItem = menuItem->platformData;
    id nsMenuItem = macMenuItem->MenuItem;

    // Update checkbox / radio item
    if( callbackData->menuItemType == Checkbox) {
        // Toggle state
        bool state = msg(nsMenuItem, s("state"));
        msg(nsMenuItem, s("setState:"), (state? NSControlStateValueOff : NSControlStateValueOn));
    } else if( callbackData->menuItemType == Radio ) {
        // Check the menu items' current state
        bool selected = msg(nsMenuItem, s("state"));

        // If it's already selected, exit early
        if (selected) return;

        int i=0; const char *groupMenuItemID;
        vec_foreach(&menuItem->radioGroup, groupMenuItemID, i) {
            // Get member
            MenuItem* groupMember = HASHMAP_GET(manager->menuItems, groupMenuItemID);
            MacMenuItem* groupMacMenuItem = (MacMenuItem*) groupMember->platformData;
            msg(groupMacMenuItem->MenuItem, s("setState:"), NSControlStateValueOff);
        }

        // check the selected menu item
        msg(nsMenuItem, s("setState:"), NSControlStateValueOn);
    }

    message = CreateMenuClickedMessage(callbackData->menuItemID, manager->contextMenuData);

    // Notify the backend
    messageFromWindowCallback(message);
    MEMFREE(message);
}
