//
// Created by Lea Anthony on 12/1/21.
//

#include "minunit.h"
#include "menu.h"

#define empty "{\"I\":\"T1\"}"
#define emptyExpected "{\"ID\":\"T1\",\"Label\":null,\"Icon\":null,\"Menu\":null}"
#define labelOnly "{\"I\":\"T1\",\"l\":\"test\"}"
#define labelOnlyExpected "{\"ID\":\"T1\",\"Label\":\"test\",\"Icon\":null,\"Menu\":null}"
#define iconOnly "{\"I\":\"T1\",\"i\":\"svelte\"}"
#define iconOnlyExpected "{\"ID\":\"T1\",\"Label\":null,\"Icon\":\"svelte\",\"Menu\":null}"
#define iconLabel "{\"I\":\"T1\",\"l\":\"test\",\"i\":\"svelte\"}"
#define iconLabelExpected "{\"ID\":\"T1\",\"Label\":\"test\",\"Icon\":\"svelte\",\"Menu\":null}"
#define blankLabel "{\"I\":\"T1\"}"
#define blankLabelExpected "{\"ID\":\"T1\",\"Label\":null,\"Icon\":null,\"Menu\":null}"
#define blankMenu "{\"I\":\"T1\"}"
#define blankMenuExpected "{\"ID\":\"T1\",\"Label\":null,\"Icon\":null,\"Menu\":null}"
#define menuTextItem "{\"I\":\"T1\",\"l\":\"test\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"t\"}]}"
#define menuTextItemExpected "{\"ID\":\"T1\",\"Label\":\"test\",\"Icon\":null,\"Menu\":{\"Label\":\"\",\"Items\":[{\"ID\":\"1\",\"label\":\"test\",\"alternateLabel\":null,\"disabled\":false,\"hidden\":false,\"colour\":null,\"font\":null,\"fontsize\":0,\"image\":null,\"acceleratorKey\":null,\"hasCallback\":false,\"type\":\"Text\",\"checked\":false}]}}"
#define checkboxItem "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"c\",\"c\":true}]}"
#define checkboxItemExpected "{\"ID\":\"T1\",\"Label\":null,\"Icon\":null,\"Menu\":{\"Label\":\"\",\"Items\":[{\"ID\":\"1\",\"label\":\"test\",\"alternateLabel\":null,\"disabled\":false,\"hidden\":false,\"colour\":null,\"font\":null,\"fontsize\":0,\"image\":null,\"acceleratorKey\":null,\"hasCallback\":false,\"type\":\"Checkbox\",\"checked\":true}]}}"
#define radioGroupItems "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"option 1\",\"t\":\"r\",\"c\":true},{\"I\":\"2\",\"l\":\"option 2\",\"t\":\"r\"},{\"I\":\"3\",\"l\":\"option 3\",\"t\":\"r\"}],\"r\":[{\"Members\":[\"1\",\"2\",\"3\"],\"Length\":3}]}"
#define radioGroupItemsExpected ""
#define callbackItem "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"Preferences\",\"t\":\"t\",\"C\":true}]}"
#define callbackItemExpected ""

const char* tests[] = {
        empty, emptyExpected,
        labelOnly, labelOnlyExpected,
        iconOnly, iconOnlyExpected,
        iconLabel, iconLabelExpected,
        blankLabel, blankLabelExpected,
        blankMenu, blankMenuExpected,
        menuTextItem, menuTextItemExpected,
        checkboxItem, checkboxItemExpected,
        radioGroupItems, radioGroupItemsExpected,
        callbackItem, callbackItemExpected,
};

MU_TEST(manager_creation) {
    MenuManager* manager = NewMenuManager();
    mu_assert(manager->applicationMenu == NULL, "app menu");
    mu_assert(manager->contextMenuData == NULL, "context menu data");
    mu_assert_int_eq(hashmap_num_entries(&manager->contextMenus), 0);
    mu_assert_int_eq(hashmap_num_entries(&manager->trayMenus), 0);
    mu_assert_int_eq(hashmap_num_entries(&manager->menuItems), 0);
    DeleteMenuManager(manager);
}

MU_TEST(add_tray) {
    for( int count = 0; count < sizeof(tests) / sizeof(tests[0]); count += 2 ) {
        MenuManager* manager = NewMenuManager();
        TrayMenu* tray = AddTrayMenu(manager, tests[count]);
        const char* trayJSON = TrayMenuAsJSON(tray);
        mu_assert_string_eq(tests[count+1], trayJSON);
        DeleteMenuManager(manager);
    }
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(manager_creation);
    MU_RUN_TEST(add_tray);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
