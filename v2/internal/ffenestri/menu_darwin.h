//
// Created by Lea Anthony on 18/1/21.
//

#include "common.h"
#include "menu.h"

typedef struct {
    id Menu;
} MacMenu;

typedef struct {
    id MenuItem;
} MacMenuItem;

typedef struct {
    id statusBarItem;
    int iconPosition;
} MacTrayMenu;

void PlatformMenuItemCallback(id self, SEL cmd, id sender);
