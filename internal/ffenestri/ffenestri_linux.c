
#ifndef __FFENESTRI_LINUX_H__
#define __FFENESTRI_LINUX_H__

#include "gtk/gtk.h"
#include "webkit2/webkit2.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// References to assets
extern const unsigned char *assets[];
extern const unsigned char runtime;
extern const char *icon[];

// Constants
#define PRIMARY_MOUSE_BUTTON 1
#define MIDDLE_MOUSE_BUTTON 2
#define SECONDARY_MOUSE_BUTTON 3

// MAIN DEBUG FLAG
int debug;

// Credit: https://stackoverflow.com/a/8465083
char *concat(const char *s1, const char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

// Debug works like sprintf but mutes if the global debug flag is true
// Credit: https://stackoverflow.com/a/20639708
void Debug(char *message, ...)
{
    if (debug)
    {
        char *temp = concat("TRACE | Ffenestri (C) | ", message);
        message = concat(temp, "\n");
        free(temp);
        va_list args;
        va_start(args, message);
        vprintf(message, args);
        free(message);
        va_end(args);
    }
}

extern void messageFromWindowCallback(const char *);
typedef void (*ffenestriCallback)(const char *);

struct Application
{

    // Gtk Data
    GtkApplication *application;
    GtkWindow *mainWindow;
    GtkWidget *webView;
    int signalInvoke;
    int signalWindowDrag;
    int signalButtonPressed;
    int signalButtonReleased;
    int signalLoadChanged;

    // Saves the events for the drag mouse button
    GdkEventButton *dragButtonEvent;

    // The number of the default drag button
    int dragButton;

    // Window Data
    const char *title;
    char *id;
    int width;
    int height;
    int resizable;
    int devtools;
    int fullscreen;
    int minWidth;
    int minHeight;
    int maxWidth;
    int maxHeight;
    int frame;

    // User Data
    char *HTML;

    // Callback
    ffenestriCallback sendMessageToBackend;

    // Bindings
    const char *bindings;

    // Lock - used for sync operations (Should we be using g_mutex?)
    int lock;
};

void *NewApplication(const char *title, int width, int height, int resizable, int devtools, int fullscreen)
{
    // Setup main application struct
    struct Application *result = malloc(sizeof(struct Application));
    result->title = title;
    result->width = width;
    result->height = height;
    result->resizable = resizable;
    result->devtools = devtools;
    result->fullscreen = fullscreen;
    result->minWidth = 0;
    result->minHeight = 0;
    result->maxWidth = 0;
    result->maxHeight = 0;
    result->frame = 1;

    // Default drag button is PRIMARY
    result->dragButton = PRIMARY_MOUSE_BUTTON;

    // printf("\n\nWidth: %d\n", result->width);
    // printf("Height: %d\n\n", result->height);

    // Features

    result->sendMessageToBackend = (ffenestriCallback)messageFromWindowCallback;

    // Create a unique ID based on the current unix timestamp
    char temp[11];
    sprintf(&temp[0], "%d", (int)time(NULL));
    result->id = concat("wails.app", &temp[0]);

    // Create the main GTK application
    GApplicationFlags flags = G_APPLICATION_FLAGS_NONE;
    result->application = gtk_application_new(result->id, flags);

    // Return the application struct
    return (void *)result;
}

void DestroyApplication(void *appPointer)
{
    Debug("Destroying Application");
    struct Application *app = (struct Application *)appPointer;

    g_application_quit(G_APPLICATION(app->application));

    // Release the GTK ID string
    if (app->id != NULL)
    {
        free(app->id);
        app->id = NULL;
    }
    else
    {
        Debug("Almost a double free for app->id");
    }

    // Free the bindings
    if (app->bindings != NULL)
    {
        free((void *)app->bindings);
        app->bindings = NULL;
    }
    else
    {
        Debug("Almost a double free for app->bindings");
    }

    // Disconnect signal handlers
    WebKitUserContentManager *manager = webkit_web_view_get_user_content_manager((WebKitWebView *)app->webView);
    g_signal_handler_disconnect(manager, app->signalInvoke);
    g_signal_handler_disconnect(manager, app->signalWindowDrag);
    g_signal_handler_disconnect(app->webView, app->signalButtonPressed);
    g_signal_handler_disconnect(app->webView, app->signalButtonReleased);
    g_signal_handler_disconnect(app->webView, app->signalLoadChanged);

    // Release the main GTK Application
    if (app->application != NULL)
    {
        g_object_unref(app->application);
        app->application = NULL;
    }
    else
    {
        Debug("Almost a double free for app->application");
    }
    Debug("Finished Destroying Application");
}

// Quit will stop the gtk application and free up all the memory
// used by the application
void Quit(void *appPointer)
{
    Debug("Quit Called");
    struct Application *app = (struct Application *)appPointer;
    gtk_window_close((GtkWindow *)app->mainWindow);
    g_application_quit((GApplication *)app->application);
    DestroyApplication(appPointer);
}

// SetTitle sets the main window title to the given string
void SetTitle(void *appPointer, const char *title)
{
    struct Application *app = (struct Application *)appPointer;
    gtk_window_set_title(app->mainWindow, title);
}

// Fullscreen sets the main window to be fullscreen
void Fullscreen(void *appPointer)
{
    struct Application *app = (struct Application *)appPointer;
    gtk_window_fullscreen(app->mainWindow);
}

// UnFullscreen resets the main window after a fullscreen
void UnFullscreen(void *appPointer)
{
    struct Application *app = (struct Application *)appPointer;
    gtk_window_unfullscreen(app->mainWindow);
}

void Center(void *appPointer)
{
    struct Application *app = (struct Application *)appPointer;
    gtk_window_set_position(app->mainWindow, GTK_WIN_POS_CENTER);
}

void setMinMaxSize(void *appPointer)
{
    struct Application *app = (struct Application *)appPointer;
    GdkGeometry size;
    size.min_width = size.min_height = size.max_width = size.max_height = 0;
    int flags = 0;
    if (app->maxHeight > 0 && app->maxWidth > 0)
    {
        size.max_height = app->maxHeight;
        size.max_width = app->maxWidth;
        flags |= GDK_HINT_MAX_SIZE;
    }
    if (app->minHeight > 0 && app->minWidth > 0)
    {
        size.min_height = app->minHeight;
        size.min_width = app->minWidth;
        flags |= GDK_HINT_MIN_SIZE;
    }
    Debug("size: %dx%d", app->width, app->height);
    Debug("min: %dx%d", size.min_width, size.min_height);
    Debug("max: %dx%d", size.max_width, size.max_height);
    gtk_window_set_geometry_hints(app->mainWindow, NULL, &size, flags);
}

// OpenFileDialog opens a dialog to select a file
// NOTE: The result is a string that will need to be freed!
char *OpenFileDialog(void *appPointer, char *title)
{
    struct Application *app = (struct Application *)appPointer;
    GtkFileChooserNative *native;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    char *filename;

    native = gtk_file_chooser_native_new(title,
                                         app->mainWindow,
                                         action,
                                         "_Open",
                                         "_Cancel");

    res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(native);
        filename = gtk_file_chooser_get_filename(chooser);
    }

    g_object_unref(native);

    return filename;
}

// SaveFileDialog opens a dialog to select a file
// NOTE: The result is a string that will need to be freed!
char *SaveFileDialog(void *appPointer, char *title)
{
    struct Application *app = (struct Application *)appPointer;
    GtkFileChooserNative *native;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;
    char *filename;

    native = gtk_file_chooser_native_new(title,
                                         app->mainWindow,
                                         action,
                                         "_Save",
                                         "_Cancel");

    res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(native);
        filename = gtk_file_chooser_get_filename(chooser);
    }

    g_object_unref(native);

    return filename;
}

// OpenDirectoryDialog opens a dialog to select a directory
// NOTE: The result is a string that will need to be freed!
char *OpenDirectoryDialog(void *appPointer, char *title)
{
    struct Application *app = (struct Application *)appPointer;
    GtkFileChooserNative *native;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
    gint res;
    char *foldername;

    native = gtk_file_chooser_native_new(title,
                                         app->mainWindow,
                                         action,
                                         "_Open",
                                         "_Cancel");

    res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(native);
        foldername = gtk_file_chooser_get_filename(chooser);
    }

    g_object_unref(native);

    return foldername;
}

void SetMinWindowSize(void *appPointer, int minWidth, int minHeight)
{
    struct Application *app = (struct Application *)appPointer;
    app->minWidth = minWidth;
    app->minHeight = minHeight;
}

void SetMaxWindowSize(void *appPointer, int maxWidth, int maxHeight)
{
    struct Application *app = (struct Application *)appPointer;
    app->maxWidth = maxWidth;
    app->maxHeight = maxHeight;
}

// SetColour sets the colour of the webview to the given colour string
int SetColour(void *appPointer, const char *colourString)
{
    struct Application *app = (struct Application *)appPointer;
    GdkRGBA rgba;
    gboolean result = gdk_rgba_parse(&rgba, colourString);
    if (result == FALSE)
    {
        return 0;
    }
    Debug("Setting webview colour to: %s", colourString);
    webkit_web_view_get_background_color((WebKitWebView *)(app->webView), &rgba);
    return 1;
}

// DisableFrame disables the window frame
void DisableFrame(void *appPointer)
{
    struct Application *app = (struct Application *)appPointer;
    app->frame = 0;
}

void syncCallback(GObject *source_object,
                  GAsyncResult *res,
                  gpointer user_data)
{

    struct Application *app = (struct Application *)user_data;
    app->lock = 0;
}

void syncEval(struct Application *app, const gchar *script)
{

    WebKitWebView *webView = (WebKitWebView *)(app->webView);
    // Debug("[%p] webview\n", webView);
    // Debug("[%p] Running sync\n", script);

    // wait for lock to free
    while (app->lock == 1)
    {
        g_main_context_iteration(0, true);
    }
    // Set lock
    app->lock = 1;

    //
    webkit_web_view_run_javascript(
        webView,
        script,
        NULL, syncCallback, app);

    while (app->lock == 1)
    {
        // Debug("[%p] Waiting for callback\n", script);
        g_main_context_iteration(0, true);
    }
    // Debug("[%p] Finished\n", script);
}

void asyncEval(WebKitWebView *webView, const gchar *script)
{
    webkit_web_view_run_javascript(
        webView,
        script,
        NULL, NULL, NULL);
}

typedef void (*dispatchMethod)(void *app, void *);

struct dispatchData
{
    struct Application *app;
    dispatchMethod method;
    void *args;
};

gboolean executeMethod(gpointer data)
{
    struct dispatchData *d = (struct dispatchData *)data;
    struct Application *app = (struct Application *)(d->app);
    // Debug("Webview %p\n", app->webView);
    // Debug("Args %s\n", d->args);
    // Debug("Method %p\n", (d->method));
    (d->method)(app, d->args);
    // Debug("Method Execute Complete. Freeing memory");
    g_free(d);
    return FALSE;
}

void ExecJS(void *app, char *js)
{
    struct dispatchData *data =
        (struct dispatchData *)g_new(struct dispatchData, 1);
    data->method = (dispatchMethod)syncEval;
    data->args = js;
    data->app = app;

    gdk_threads_add_idle(executeMethod, data);
}

typedef char *(*dialogMethod)(void *app, void *);

struct dialogCall
{
    struct Application *app;
    dialogMethod method;
    void *args;
    char *result;
    int done;
};

gboolean executeMethodWithReturn(gpointer data)
{
    struct dialogCall *d = (struct dialogCall *)data;
    struct Application *app = (struct Application *)(d->app);
    Debug("Webview %p\n", app->webView);
    Debug("Args %s\n", d->args);
    Debug("Method %p\n", (d->method));
    d->result = (d->method)(app, d->args);
    d->done = 1;
    // Debug("Method Execute Complete. Freeing memory");
    return FALSE;
}

char *OpenFileDialogOnMainThread(void *app, char *title)
{
    struct dialogCall *data =
        (struct dialogCall *)g_new(struct dialogCall, 1);
    data->result = NULL;
    data->done = 0;
    data->method = (dialogMethod)OpenFileDialog;
    data->args = title;
    data->app = app;

    gdk_threads_add_idle(executeMethodWithReturn, data);

    while (data->done == 0)
    {
        // Debug("Waiting for dialog");
        usleep(100000);
    }
    Debug("Dialog done");
    Debug("Result = %s\n", data->result);
    g_free(data);
    // Fingers crossed this wasn't freed by g_free above
    return data->result;
}

char *SaveFileDialogOnMainThread(void *app, char *title)
{
    struct dialogCall *data =
        (struct dialogCall *)g_new(struct dialogCall, 1);
    data->result = NULL;
    data->done = 0;
    data->method = (dialogMethod)SaveFileDialog;
    data->args = title;
    data->app = app;

    gdk_threads_add_idle(executeMethodWithReturn, data);

    while (data->done == 0)
    {
        // Debug("Waiting for dialog");
        usleep(100000);
    }
    Debug("Dialog done");
    Debug("Result = %s\n", data->result);
    g_free(data);
    // Fingers crossed this wasn't freed by g_free above
    return data->result;
}

char *OpenDirectoryDialogOnMainThread(void *app, char *title)
{
    struct dialogCall *data =
        (struct dialogCall *)g_new(struct dialogCall, 1);
    data->result = NULL;
    data->done = 0;
    data->method = (dialogMethod)OpenDirectoryDialog;
    data->args = title;
    data->app = app;

    gdk_threads_add_idle(executeMethodWithReturn, data);

    while (data->done == 0)
    {
        // Debug("Waiting for dialog");
        usleep(100000);
    }
    Debug("Directory Dialog done");
    Debug("Result = %s\n", data->result);
    g_free(data);
    // Fingers crossed this wasn't freed by g_free above
    return data->result;
}

// Sets the icon to the XPM stored in icon
void setIcon(struct Application *app)
{
    GdkPixbuf *appIcon = gdk_pixbuf_new_from_xpm_data((const char **)icon);
    gtk_window_set_icon(app->mainWindow, appIcon);
}

static void load_finished_cb(WebKitWebView *webView,
                             WebKitLoadEvent load_event,
                             gpointer userData)
{
    struct Application *app;

    switch (load_event)
    {
    // case WEBKIT_LOAD_STARTED:
    //     /* New load, we have now a provisional URI */
    //     // printf("Start downloading %s\n", webkit_web_view_get_uri(web_view));
    //     /* Here we could start a spinner or update the
    //      * location bar with the provisional URI */
    //     break;
    // case WEBKIT_LOAD_REDIRECTED:
    //     // printf("Redirected to: %s\n", webkit_web_view_get_uri(web_view));
    //     break;
    // case WEBKIT_LOAD_COMMITTED:
    //     /* The load is being performed. Current URI is
    //      * the final one and it won't change unless a new
    //      * load is requested or a navigation within the
    //      * same page is performed */
    //     // printf("Loading: %s\n", webkit_web_view_get_uri(web_view));
    //     break;
    case WEBKIT_LOAD_FINISHED:
        /* Load finished, we can now stop the spinner */
        // printf("Finished loading: %s\n", webkit_web_view_get_uri(web_view));
        app = (struct Application *)userData;

        // Bindings
        Debug("Binding Methods");
        syncEval(app, app->bindings);

        // Runtime
        Debug("Setting up Wails runtime");
        syncEval(app, &runtime);

        // Loop over assets
        int index = 1;
        while (1)
        {
            // Get next asset pointer
            const char *asset = assets[index];

            // If we have no more assets, break
            if (asset == 0x00)
            {
                break;
            }

            // sync eval the asset
            syncEval(app, asset);
            index++;
        };

        // Set the icon
        setIcon(app);

        // Setup fullscreen
        if (app->fullscreen)
        {
            Debug("Going fullscreen");
            Fullscreen(app);
        }

        // Setup resize
        gtk_window_resize(GTK_WINDOW(app->mainWindow), app->width, app->height);

        if (app->resizable)
        {
            gtk_window_set_default_size(GTK_WINDOW(app->mainWindow), app->width, app->height);
        }
        else
        {
            gtk_widget_set_size_request(GTK_WIDGET(app->mainWindow), app->width, app->height);
            gtk_window_resize(GTK_WINDOW(app->mainWindow), app->width, app->height);
            // Fix the min/max to the window size for good measure
            app->minHeight = app->maxHeight = app->height;
            app->minWidth = app->maxWidth = app->width;
        }
        gtk_window_set_resizable(GTK_WINDOW(app->mainWindow), app->resizable ? TRUE : FALSE);
        setMinMaxSize(app);

        // Centre by default
        Center(app);

        // Show window and focus
        gtk_widget_show_all(GTK_WIDGET(app->mainWindow));
        gtk_widget_grab_focus(app->webView);
        break;
    }
}

static gboolean
disable_context_menu_cb(WebKitWebView *web_view,
                        WebKitContextMenu *context_menu,
                        GdkEvent *event,
                        WebKitHitTestResult *hit_test_result,
                        gpointer user_data)
{
    return TRUE;
}

static void printEvent(const char *message, GdkEventButton *event)
{
    Debug("%s: [button:%d] [x:%f] [y:%f] [time:%d]",
          message,
          event->button,
          event->x_root,
          event->y_root,
          event->time);
}

static void dragWindow(WebKitUserContentManager *contentManager,
                       WebKitJavascriptResult *result,
                       gpointer arg)
{
    struct Application *app = (struct Application *)arg;

    // If we get this message erroneously, ignore
    if (app->dragButtonEvent == NULL)
    {
        return;
    }

    // Ignore non-toplevel widgets
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(app->webView));
    if (!GTK_IS_WINDOW(window))
    {
        return;
    }

    // Initiate the drag
    printEvent("Starting drag with event", app->dragButtonEvent);

    gtk_window_begin_move_drag(app->mainWindow,
                               app->dragButton,
                               app->dragButtonEvent->x_root,
                               app->dragButtonEvent->y_root,
                               app->dragButtonEvent->time);
    // Clear the event
    app->dragButtonEvent = NULL;

    return FALSE;
}

gboolean buttonPress(GtkWidget *widget, GdkEventButton *event, gpointer arg)
{
    struct Application *app = (struct Application *)arg;
    Debug("I am pressing a button");

    if (event->type == GDK_BUTTON_PRESS && event->button == app->dragButton)
    {
        printEvent("Drag button event was saved", event);
        app->dragButtonEvent = event;
    }
    return FALSE;
}

gboolean buttonRelease(GtkWidget *widget, GdkEventButton *event, gpointer arg)
{
    struct Application *app = (struct Application *)arg;
    Debug("I am releasing a button");

    if (event->type == GDK_BUTTON_RELEASE && event->button == app->dragButton)
    {
        printEvent("Drag button event was reset", event);

        app->dragButtonEvent = NULL;
    }
    return FALSE;
}

static void sendMessageToBackend(WebKitUserContentManager *contentManager,
                                 WebKitJavascriptResult *result,
                                 gpointer arg)
{
    struct Application *app = (struct Application *)arg;
#if WEBKIT_MAJOR_VERSION >= 2 && WEBKIT_MINOR_VERSION >= 22
    JSCValue *value = webkit_javascript_result_get_js_value(result);
    char *message = jsc_value_to_string(value);
#else
    JSGlobalContextRef context = webkit_javascript_result_get_global_context(result);
    JSValueRef value = webkit_javascript_result_get_value(result);
    JSStringRef js = JSValueToStringCopy(context, value, NULL);
    size_t messageSize = JSStringGetMaximumUTF8CStringSize(js);
    char *message = g_new(char, messageSize);
    JSStringGetUTF8CString(js, message, messageSize);
    JSStringRelease(js);
#endif
    app->sendMessageToBackend(message);
    g_free(message);
}

void SetDebug(void *applicationPointer, int flag)
{
    struct Application *app = (struct Application *)applicationPointer;
    debug = flag;
}

void SetBindings(void *applicationPointer, const char *bindings)
{
    struct Application *app = (struct Application *)applicationPointer;

    const char *temp = concat("window.wailsbindings = \"", bindings);
    const char *jscall = concat(temp, "\";");
    free((void *)temp);
    app->bindings = jscall;
}

// This is called when the close button on the window is pressed
gboolean close_button_pressed(GtkWidget *widget,
                              GdkEvent *event,
                              gpointer user_data)
{
    struct Application *app = (struct Application *)user_data;
    app->sendMessageToBackend("WC"); // Window Close
    return TRUE;
}

static void setupWindow(void *applicationPointer)
{

    struct Application *app = (struct Application *)applicationPointer;

    // Create the window
    GtkWidget *mainWindow = gtk_application_window_new(app->application);
    // Save reference
    app->mainWindow = GTK_WINDOW(mainWindow);

    // Setup frame
    gtk_window_set_decorated((GtkWindow *)mainWindow, app->frame);

    // Setup title
    gtk_window_set_title(GTK_WINDOW(mainWindow), app->title);

    // Setup script handler
    WebKitUserContentManager *contentManager = webkit_user_content_manager_new();

    // Setup the invoke handler
    webkit_user_content_manager_register_script_message_handler(contentManager, "external");
    app->signalInvoke = g_signal_connect(contentManager, "script-message-received::external", G_CALLBACK(sendMessageToBackend), app);

    // Setup the window drag handler
    webkit_user_content_manager_register_script_message_handler(contentManager, "windowDrag");
    app->signalWindowDrag = g_signal_connect(contentManager, "script-message-received::windowDrag", G_CALLBACK(dragWindow), app);

    GtkWidget *webView = webkit_web_view_new_with_user_content_manager(contentManager);

    // Save reference
    app->webView = webView;

    // Add the webview to the window
    gtk_container_add(GTK_CONTAINER(mainWindow), webView);

    // Setup the mouse handlers
    app->signalButtonPressed = g_signal_connect(app->webView, "button-press-event", G_CALLBACK(buttonPress), app);
    app->signalButtonReleased = g_signal_connect(app->webView, "button-release-event", G_CALLBACK(buttonRelease), app);

    // Load default HTML
    app->signalLoadChanged = g_signal_connect(G_OBJECT(webView), "load-changed", G_CALLBACK(load_finished_cb), app);

    // Load the user's HTML
    // assets[0] is the HTML because the asset array is bundled like that by convention
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webView), assets[0]);

    // Check if we want to enable the dev tools
    if (app->devtools)
    {
        WebKitSettings *settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webView));
        // webkit_settings_set_enable_write_console_messages_to_stdout(settings, true);
        webkit_settings_set_enable_developer_extras(settings, true);
    }
    else
    {
        g_signal_connect(G_OBJECT(webView), "context-menu", G_CALLBACK(disable_context_menu_cb), app);
    }

    // Listen for close button signal
    g_signal_connect(GTK_WIDGET(mainWindow), "delete-event", G_CALLBACK(close_button_pressed), app);
}

static void
activate(GtkApplication *app,
         gpointer user_data)
{
    struct Application *mainApp = (struct Application *)user_data;

    // Main Window
    setupWindow(mainApp);
}

void Run(void *applicationPointer, int argc, char **argv)
{
    struct Application *app = (struct Application *)applicationPointer;

    g_signal_connect(app->application, "activate", G_CALLBACK(activate), app);
    g_application_run(G_APPLICATION(app->application), argc, argv);
}

#endif
