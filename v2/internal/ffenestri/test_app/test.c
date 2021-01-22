//
// Created by Lea Anthony on 12/1/21.
//

#include "ffenestri.h"
#include "ffenestri_darwin.h"

#define empty "{\"I\":\"T1\"}"
#define labelOnly "{\"I\":\"T1\",\"l\":\"test\"}"
#define iconOnly "{\"I\":\"T1\",\"i\":\"svelte\"}"
#define iconLabel "{\"I\":\"T1\",\"l\":\"test\",\"i\":\"svelte\"}"
#define blankLabel "{\"I\":\"T1\"}"
#define blankMenu "{\"I\":\"T1\"}"
#define menuTextItem "{\"I\":\"T1\",\"l\":\"test\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"t\"}]}"
#define checkboxItem "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"c\",\"c\":true}]}"
#define radioGroupItems "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"option 1\",\"t\":\"r\",\"c\":true},{\"I\":\"2\",\"l\":\"option 2\",\"t\":\"r\"},{\"I\":\"3\",\"l\":\"option 3\",\"t\":\"r\"}],\"r\":[{\"Members\":[\"1\",\"2\",\"3\"],\"Length\":3}]}"
#define callbackItem "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"Preferences\",\"t\":\"t\",\"C\":true}]}"

#define menuTextItemOnly "{\"I\":\"T1\",\"m\":{\"I\":\"M1\",\"i\":[{\"I\":\"1\",\"l\":\"Preferences\",\"t\":\"t\",\"C\":true}]}}"
#define menuTextItemLabel "{\"I\":\"T1\",\"l\":\"Tray Label!\",\"m\":{\"I\":\"M1\",\"i\":[{\"I\":\"1\",\"l\":\"Preferences\",\"t\":\"t\",\"C\":true}]}}"
#define menuTextItemIcon "{\"I\":\"T1\",\"i\":\"svelte\",\"m\":{\"I\":\"M1\",\"i\":[{\"I\":\"1\",\"l\":\"Preferences\",\"t\":\"t\",\"C\":true}]}}"
#define menuTextItemIconLabel "{\"I\":\"T1\",\"l\":\"Tray Label!\",\"i\":\"svelte\",\"m\":{\"I\":\"M1\",\"i\":[{\"I\":\"1\",\"l\":\"Preferences\",\"t\":\"t\",\"C\":true}]}}"

bool startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
            lenstr = strlen(str);
    return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}

void *app;
//char *options = "{\"Title\":\"Kitchen Sink\",\"Width\":1024,\"Height\":768,\"DisableResize\":false,\"Fullscreen\":false,\"MinWidth\":800,\"MinHeight\":600,\"MaxWidth\":0,\"MaxHeight\":0,\"StartHidden\":false,\"DevTools\":true,\"RGBA\":4294967295,\"LogLevel\":1}";
//char *bindings = "{\\\"main\\\":{\\\"Browser\\\":{\\\"Open\\\":{\\\"name\\\":\\\"main.Browser.Open\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"error\\\"}]},\\\"WailsInit\\\":{\\\"name\\\":\\\"main.Browser.WailsInit\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*runtime.Runtime\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"error\\\"}]}},\\\"ContextMenu\\\":{\\\"WailsInit\\\":{\\\"name\\\":\\\"main.ContextMenu.WailsInit\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*runtime.Runtime\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"error\\\"}]}},\\\"Dialog\\\":{\\\"Message\\\":{\\\"name\\\":\\\"main.Dialog.Message\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*dialog.MessageDialog\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"Open\\\":{\\\"name\\\":\\\"main.Dialog.Open\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*dialog.OpenDialog\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"[]string\\\"}]},\\\"Save\\\":{\\\"name\\\":\\\"main.Dialog.Save\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*dialog.SaveDialog\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"WailsInit\\\":{\\\"name\\\":\\\"main.Dialog.WailsInit\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*runtime.Runtime\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"error\\\"}]}},\\\"Events\\\":{\\\"Emit\\\":{\\\"name\\\":\\\"main.Events.Emit\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"},{\\\"type\\\":\\\"[]interface {}\\\"}]},\\\"On\\\":{\\\"name\\\":\\\"main.Events.On\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"OnMultiple\\\":{\\\"name\\\":\\\"main.Events.OnMultiple\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"},{\\\"type\\\":\\\"int\\\"}]},\\\"Once\\\":{\\\"name\\\":\\\"main.Events.Once\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"WailsInit\\\":{\\\"name\\\":\\\"main.Events.WailsInit\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*runtime.Runtime\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"error\\\"}]}},\\\"Logger\\\":{\\\"Debug\\\":{\\\"name\\\":\\\"main.Logger.Debug\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"Error\\\":{\\\"name\\\":\\\"main.Logger.Error\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"Fatal\\\":{\\\"name\\\":\\\"main.Logger.Fatal\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"Info\\\":{\\\"name\\\":\\\"main.Logger.Info\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"Print\\\":{\\\"name\\\":\\\"main.Logger.Print\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"SetLogLevel\\\":{\\\"name\\\":\\\"main.Logger.SetLogLevel\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"logger.LogLevel\\\"}]},\\\"Trace\\\":{\\\"name\\\":\\\"main.Logger.Trace\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"WailsInit\\\":{\\\"name\\\":\\\"main.Logger.WailsInit\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*runtime.Runtime\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"error\\\"}]},\\\"Warning\\\":{\\\"name\\\":\\\"main.Logger.Warning\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}]}},\\\"Menu\\\":{\\\"WailsInit\\\":{\\\"name\\\":\\\"main.Menu.WailsInit\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*runtime.Runtime\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"error\\\"}]}},\\\"System\\\":{\\\"Platform\\\":{\\\"name\\\":\\\"main.System.Platform\\\",\\\"outputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"WailsInit\\\":{\\\"name\\\":\\\"main.System.WailsInit\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*runtime.Runtime\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"error\\\"}]}},\\\"Tray\\\":{\\\"DarkIcon\\\":{\\\"name\\\":\\\"main.Tray.DarkIcon\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*menu.CallbackData\\\"}]},\\\"LightIcon\\\":{\\\"name\\\":\\\"main.Tray.LightIcon\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*menu.CallbackData\\\"}]},\\\"NoIcon\\\":{\\\"name\\\":\\\"main.Tray.NoIcon\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*menu.CallbackData\\\"}]},\\\"SvelteIcon\\\":{\\\"name\\\":\\\"main.Tray.SvelteIcon\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*menu.CallbackData\\\"}]}},\\\"Window\\\":{\\\"Center\\\":{\\\"name\\\":\\\"main.Window.Center\\\"},\\\"Close\\\":{\\\"name\\\":\\\"main.Window.Close\\\"},\\\"Fullscreen\\\":{\\\"name\\\":\\\"main.Window.Fullscreen\\\"},\\\"Hide\\\":{\\\"name\\\":\\\"main.Window.Hide\\\"},\\\"Maximise\\\":{\\\"name\\\":\\\"main.Window.Maximise\\\"},\\\"Minimise\\\":{\\\"name\\\":\\\"main.Window.Minimise\\\"},\\\"SetPosition\\\":{\\\"name\\\":\\\"main.Window.SetPosition\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"int\\\"},{\\\"type\\\":\\\"int\\\"}]},\\\"SetSize\\\":{\\\"name\\\":\\\"main.Window.SetSize\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"int\\\"},{\\\"type\\\":\\\"int\\\"}]},\\\"SetTitle\\\":{\\\"name\\\":\\\"main.Window.SetTitle\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"string\\\"}]},\\\"Show\\\":{\\\"name\\\":\\\"main.Window.Show\\\"},\\\"UnFullscreen\\\":{\\\"name\\\":\\\"main.Window.UnFullscreen\\\"},\\\"Unmaximise\\\":{\\\"name\\\":\\\"main.Window.Unmaximise\\\"},\\\"Unminimise\\\":{\\\"name\\\":\\\"main.Window.Unminimise\\\"},\\\"WailsInit\\\":{\\\"name\\\":\\\"main.Window.WailsInit\\\",\\\"inputs\\\":[{\\\"type\\\":\\\"*runtime.Runtime\\\"}],\\\"outputs\\\":[{\\\"type\\\":\\\"error\\\"}]}}}}";
//char *platformOptions = "{\"AppMenu\":\"\",\"TrayMenus\":\"[{\\\"I\\\":\\\"T1\\\",\\\"l\\\":\\\"Test Tray Label\\\",\\\"m\\\":[{\\\"I\\\":\\\"1\\\",\\\"l\\\":\\\"Show Window\\\",\\\"t\\\":\\\"t\\\",\\\"C\\\":true},{\\\"I\\\":\\\"2\\\",\\\"l\\\":\\\"Hide Window\\\",\\\"t\\\":\\\"t\\\",\\\"C\\\":true},{\\\"I\\\":\\\"3\\\",\\\"l\\\":\\\"Minimise Window\\\",\\\"t\\\":\\\"t\\\",\\\"C\\\":true},{\\\"I\\\":\\\"4\\\",\\\"l\\\":\\\"Unminimise Window\\\",\\\"t\\\":\\\"t\\\",\\\"C\\\":true}]},{\\\"I\\\":\\\"T2\\\",\\\"l\\\":\\\"Another tray label\\\",\\\"i\\\":\\\"svelte\\\",\\\"m\\\":[{\\\"I\\\":\\\"5\\\",\\\"l\\\":\\\"Update Label\\\",\\\"t\\\":\\\"t\\\",\\\"C\\\":true},{\\\"I\\\":\\\"6\\\",\\\"l\\\":\\\"Select Icon\\\",\\\"t\\\":\\\"S\\\",\\\"s\\\":[{\\\"I\\\":\\\"7\\\",\\\"l\\\":\\\"Svelte\\\",\\\"t\\\":\\\"t\\\",\\\"C\\\":true},{\\\"I\\\":\\\"8\\\",\\\"l\\\":\\\"Light\\\",\\\"t\\\":\\\"t\\\",\\\"C\\\":true},{\\\"I\\\":\\\"9\\\",\\\"l\\\":\\\"Dark\\\",\\\"t\\\":\\\"t\\\",\\\"C\\\":true},{\\\"I\\\":\\\"10\\\",\\\"l\\\":\\\"None\\\",\\\"t\\\":\\\"t\\\",\\\"C\\\":true}]}]}]\",\"ContextMenus\":\"\",\"TitleBar\":{\"TitlebarAppearsTransparent\":true,\"HideTitle\":true,\"HideTitleBar\":false,\"FullSizeContent\":true,\"UseToolbar\":true,\"HideToolbarSeparator\":true},\"Appearance\":\"\",\"WebviewIsTransparent\":true,\"WindowBackgroundIsTranslucent\":true}";
//
//char *context1 = "[{\"ID\":\"test\",\"ProcessedMenu\":{\"Menu\":{\"Items\":[{\"ID\":\"Test Context Menu\",\"Label\":\"Clicked 0 times\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"Label\":\"\",\"Type\":\"Separator\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"checkbox\",\"Label\":\"I am a checkbox\",\"Type\":\"Checkbox\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"Label\":\"\",\"Type\":\"Separator\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"Radio Option 1\",\"Label\":\"Radio Option 1\",\"Type\":\"Radio\",\"Disabled\":false,\"Hidden\":false,\"Checked\":true,\"Foreground\":0,\"Background\":0},{\"ID\":\"Radio Option 2\",\"Label\":\"Radio Option 2\",\"Type\":\"Radio\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"Radio Option 3\",\"Label\":\"Radio Option 3\",\"Type\":\"Radio\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"Label\":\"\",\"Type\":\"Separator\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"Label\":\"A Submenu\",\"Type\":\"Submenu\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"SubMenu\":{\"Items\":[{\"ID\":\"Hello\",\"Label\":\"Hello\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0}]},\"Foreground\":0,\"Background\":0}]},\"RadioGroups\":[{\"Members\":[\"Radio Option 1\",\"Radio Option 2\",\"Radio Option 3\"],\"Length\":3}]}}]";
//char *context2 = "[{\"ID\":\"test\",\"ProcessedMenu\":{\"Menu\":{\"Items\":[{\"ID\":\"Test Context Menu\",\"Label\":\"Clicked 1 times\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"Label\":\"\",\"Type\":\"Separator\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"checkbox\",\"Label\":\"I am a checkbox\",\"Type\":\"Checkbox\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"Label\":\"\",\"Type\":\"Separator\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"Radio Option 1\",\"Label\":\"Radio Option 1\",\"Type\":\"Radio\",\"Disabled\":false,\"Hidden\":false,\"Checked\":true,\"Foreground\":0,\"Background\":0},{\"ID\":\"Radio Option 2\",\"Label\":\"Radio Option 2\",\"Type\":\"Radio\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"Radio Option 3\",\"Label\":\"Radio Option 3\",\"Type\":\"Radio\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"Label\":\"\",\"Type\":\"Separator\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"Label\":\"A Submenu\",\"Type\":\"Submenu\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"SubMenu\":{\"Items\":[{\"ID\":\"Hello\",\"Label\":\"Hello\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0}]},\"Foreground\":0,\"Background\":0}]},\"RadioGroups\":[{\"Members\":[\"Radio Option 1\",\"Radio Option 2\",\"Radio Option 3\"],\"Length\":3}]}}]";
//
//char *tray1 = "{\"ID\":\"0\",\"Label\":\"Test Tray Label\",\"Icon\":\"\",\"ProcessedMenu\":{\"Menu\":{\"Items\":[{\"ID\":\"0\",\"Label\":\"Show Window\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"1\",\"Label\":\"Hide Window\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"2\",\"Label\":\"Minimise Window\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"3\",\"Label\":\"Unminimise Window\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0}]},\"RadioGroups\":null}}";
//char *tray2 = "{\"ID\":\"1\",\"Label\":\"Another tray label\",\"Icon\":\"\",\"ProcessedMenu\":{\"Menu\":{\"Items\":[{\"ID\":\"0\",\"Label\":\"Update Label\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0}]},\"RadioGroups\":null}}";
//char *tray3 = "{\"ID\":\"1\",\"Label\":\"ZOMG it works\",\"Icon\":\"\",\"ProcessedMenu\":{\"Menu\":{\"Items\":[{\"ID\":\"0\",\"Label\":\"Update Label\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0}]},\"RadioGroups\":null}}";

const char* trays[3];

int count = 1;
void messageFromWindowCallback(const char *message) {
    if( startsWith("MC", message) ) {
        printf("Menu Click: %s\n", message);
//        SetTrayMenu(app, trays[count%3]);
        count++;
    }
    printf("Fake callback %s\n", message);
}
int main(int argc, char **argv) {
//    trays[0] = "{\"I\":\"T1\"}"; // Blank menu
//    trays[0] = "{\"I\":\"T1\",\"l\":\"test\"}"; // Label Only
//    trays[0] = "{\"I\":\"T1\",\"i\":\"svelte\"}"; // Icon Only
//    trays[0] = "{\"I\":\"T1\",\"l\":\"test\",\"i\":\"svelte\"}"; // Icon + Label
//    trays[0] = "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"t\"}]}"; // Menu Only
//    trays[0] = "{\"I\":\"T1\",\"l\": \"test menu\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"c\",\"c\":true}]}"; // Checkbox Menu
//    trays[0] = "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"option 1\",\"t\":\"r\",\"c\":true},{\"I\":\"2\",\"l\":\"option 2\",\"t\":\"r\"},{\"I\":\"3\",\"l\":\"option 3\",\"t\":\"r\"}],\"r\":[{\"Members\":[\"1\",\"2\",\"3\"],\"Length\":3}]}";
    trays[0] = menuTextItemIconLabel;
//    trays[1] = "{\"ID\":\"0\",\"Label\":\"two\",\"Icon\":\"\",\"ProcessedMenu\":{\"Menu\":{\"Items\":[{\"ID\":\"0\",\"Label\":\"Preferences\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"1\",\"Label\":\"Quit\",\"Accelerator\":{\"Key\":\"q\",\"Modifiers\":[\"CmdOrCtrl\"]},\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0}]},\"RadioGroups\":null}}";
//    trays[2] = "{\"ID\":\"0\",\"Label\":\"three\",\"Icon\":\"\",\"ProcessedMenu\":{\"Menu\":{\"Items\":[{\"ID\":\"0\",\"Label\":\"Preferences\",\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0},{\"ID\":\"1\",\"Label\":\"Quit\",\"Accelerator\":{\"Key\":\"q\",\"Modifiers\":[\"CmdOrCtrl\"]},\"Type\":\"Text\",\"Disabled\":false,\"Hidden\":false,\"Checked\":false,\"Foreground\":0,\"Background\":0}]},\"RadioGroups\":null}}";

    app = NewApplication("test", 800,600,1,1,0,0,1);
//    app = NewApplication2(options, bindings, platformOptions);

    SetBindings(app, "");
//    SetContextMenus(app, context1);
    WebviewIsTransparent(app);
    HideTitle(app);
    FullSizeContent(app);
    UseToolbar(app);
    HideToolbarSeparator(app);
    TitlebarAppearsTransparent(app);
    WindowBackgroundIsTranslucent(app);
    SetTrayMenu(app, trays[0]);
    Run(app, argc, argv);
    return 0;
}
