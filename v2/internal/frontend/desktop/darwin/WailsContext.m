//
//  WailsContext.m
//  test
//
//  Created by Lea Anthony on 10/10/21.
//

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>
#import "WailsContext.h"
#import "WailsAlert.h"
#import "WailsMenu.h"
#import "WindowDelegate.h"
#import "message.h"
#import "Role.h"

@implementation WailsWindow

- (BOOL)canBecomeKeyWindow
{
    return YES;
}

- (void) applyWindowConstraints {
    [self setMinSize:self.userMinSize];
    [self setMaxSize:self.userMaxSize];
}

- (void) disableWindowConstraints {
    [self setMinSize:NSMakeSize(0, 0)];
    [self setMaxSize:NSMakeSize(FLT_MAX, FLT_MAX)];
}

@end

@implementation WailsContext

- (void) SetSize:(int)width :(int)height {
    
    if (self.shuttingDown) return;
    
    NSRect frame = [self.mainWindow frame];
    frame.origin.y += frame.size.height - height;
    frame.size.width = width;
    frame.size.height = height;
    [self.mainWindow setFrame:frame display:TRUE animate:FALSE];
}

- (void) SetPosition:(int)x :(int)y {
    
    if (self.shuttingDown) return;
    
    NSScreen* screen = [self getCurrentScreen];
    NSRect windowFrame = [self.mainWindow frame];
    NSRect screenFrame = [screen frame];
    windowFrame.origin.x = screenFrame.origin.x + (float)x;
    windowFrame.origin.y = (screenFrame.origin.y + screenFrame.size.height) - windowFrame.size.height - (float)y;
    
    [self.mainWindow setFrame:windowFrame display:TRUE animate:FALSE];
}

- (void) SetMinSize:(int)minWidth :(int)minHeight {
    
    if (self.shuttingDown) return;
    
    NSSize size = { minWidth, minHeight };
    self.mainWindow.userMinSize = size;
    [self.mainWindow setMinSize:size];
    [self adjustWindowSize];
}


- (void) SetMaxSize:(int)maxWidth :(int)maxHeight {
    
    if (self.shuttingDown) return;
    
    NSSize size = { FLT_MAX, FLT_MAX };
    
    size.width = maxWidth > 0 ? maxWidth : FLT_MAX;
    size.height = maxHeight > 0 ? maxHeight : FLT_MAX;
    
    self.mainWindow.userMaxSize = size;
    [self.mainWindow setMaxSize:size];
    [self adjustWindowSize];
}


- (void) adjustWindowSize {
    
    if (self.shuttingDown) return;
    
    NSRect currentFrame = [self.mainWindow frame];
    
    if ( currentFrame.size.width > self.mainWindow.userMaxSize.width ) currentFrame.size.width = self.mainWindow.userMaxSize.width;
    if ( currentFrame.size.width < self.mainWindow.userMinSize.width ) currentFrame.size.width = self.mainWindow.userMinSize.width;
    if ( currentFrame.size.height > self.mainWindow.userMaxSize.height ) currentFrame.size.height = self.mainWindow.userMaxSize.height;
    if ( currentFrame.size.height < self.mainWindow.userMinSize.height ) currentFrame.size.height = self.mainWindow.userMinSize.height;

    [self.mainWindow setFrame:currentFrame display:YES animate:FALSE];
    
}

- (void) dealloc {
    [self.appdelegate release];
    [self.mainWindow release];
    [self.mouseEvent release];
    [self.userContentController release];
    [self.urlRequests release];
    [self.applicationMenu release];
    [super dealloc];
}

- (NSScreen*) getCurrentScreen {
    NSScreen* screen = [self.mainWindow screen];
    if( screen == NULL ) {
        screen = [NSScreen mainScreen];
    }
    return screen;
}

- (void) SetTitle:(NSString*)title {
    [self.mainWindow setTitle:title];
}

- (void) Center {
     [self.mainWindow center];
}

- (BOOL) isFullscreen {
    NSWindowStyleMask masks = [self.mainWindow styleMask];
    if ( masks & NSWindowStyleMaskFullScreen ) {
        return YES;
    }
    return NO;
}

- (void) CreateWindow:(int)width :(int)height :(bool)frameless :(bool)resizable :(bool)fullscreen :(bool)fullSizeContent :(bool)hideTitleBar :(bool)titlebarAppearsTransparent :(bool)hideTitle :(bool)useToolbar :(bool)hideToolbarSeparator :(bool)webviewIsTransparent :(bool)hideWindowOnClose :(NSString*)appearance :(bool)windowIsTranslucent :(int)minWidth :(int)minHeight :(int)maxWidth :(int)maxHeight {
    
    self.urlRequests = [NSMutableDictionary new];
    
    NSWindowStyleMask styleMask = 0;
    
    if( !frameless ) {
        if (!hideTitleBar) {
            styleMask |= NSWindowStyleMaskTitled;
        }
        styleMask |= NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable;
    }

    if( fullSizeContent || frameless || titlebarAppearsTransparent ) {
        styleMask |= NSWindowStyleMaskFullSizeContentView;
    }

    if (resizable) {
        styleMask |= NSWindowStyleMaskResizable;
    }
    
    self.mainWindow = [[WailsWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
                                                      styleMask:styleMask backing:NSBackingStoreBuffered defer:NO];
        
    if (!frameless && useToolbar) {
        id toolbar = [[NSToolbar alloc] initWithIdentifier:@"wails.toolbar"];
        [toolbar autorelease];
        [toolbar setShowsBaselineSeparator:!hideToolbarSeparator];
        [self.mainWindow setToolbar:toolbar];
    
    }
    
    [self.mainWindow setTitleVisibility:hideTitle];
    [self.mainWindow setTitlebarAppearsTransparent:titlebarAppearsTransparent];
    
//    [self.mainWindow canBecomeKeyWindow];
    
    id contentView = [self.mainWindow contentView];
    if (windowIsTranslucent) {
        NSVisualEffectView *effectView = [NSVisualEffectView alloc];
        NSRect bounds = [contentView bounds];
        [effectView initWithFrame:bounds];
        [effectView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
        [effectView setBlendingMode:NSVisualEffectBlendingModeBehindWindow];
        [effectView setState:NSVisualEffectStateActive];
        [contentView addSubview:effectView positioned:NSWindowBelow relativeTo:nil];
    }
    
    if (appearance != nil) {
        NSAppearance *nsAppearance = [NSAppearance appearanceNamed:appearance];
        [self.mainWindow setAppearance:nsAppearance];
    }
    

    NSSize minSize = { minWidth, minHeight };
    NSSize maxSize = { maxWidth, maxHeight };
    if (maxSize.width == 0) {
        maxSize.width = FLT_MAX;
    }
    if (maxSize.height == 0) {
        maxSize.height = FLT_MAX;
    }
    self.mainWindow.userMaxSize = maxSize;
    self.mainWindow.userMinSize = minSize;
    
    if( !fullscreen ) {
        [self.mainWindow applyWindowConstraints];
    }
    
    WindowDelegate *windowDelegate = [WindowDelegate new];
    windowDelegate.hideOnClose = hideWindowOnClose;
    windowDelegate.ctx = self;
    [self.mainWindow setDelegate:windowDelegate];
    
    // Webview stuff here!
    WKWebViewConfiguration *config = [WKWebViewConfiguration new];
    config.suppressesIncrementalRendering = true;
    [config setURLSchemeHandler:self forURLScheme:@"wails"];
    
//    [config.preferences setValue:[NSNumber numberWithBool:true] forKey:@"developerExtrasEnabled"];
    
    WKUserContentController* userContentController = [WKUserContentController new];
    [userContentController addScriptMessageHandler:self name:@"external"];
    config.userContentController = userContentController;
    self.userContentController = userContentController;
    if (self.debug) {
        [config.preferences setValue:@YES forKey:@"developerExtrasEnabled"];
    } else {
        // Disable default context menus
        WKUserScript *initScript = [WKUserScript new];
        [initScript initWithSource:@"window.wails.flags.disableWailsDefaultContextMenu = true;"
                     injectionTime:WKUserScriptInjectionTimeAtDocumentEnd
                  forMainFrameOnly:false];
        [userContentController addUserScript:initScript];
        
    }
    
    self.webview = [WKWebView alloc];
    CGRect init = { 0,0,0,0 };
    [self.webview initWithFrame:init configuration:config];
    [contentView addSubview:self.webview];
    [self.webview setAutoresizingMask: NSViewWidthSizable|NSViewHeightSizable];
    CGRect contentViewBounds = [contentView bounds];
    [self.webview setFrame:contentViewBounds];
    
    if (webviewIsTransparent) {
        [self.webview setValue:[NSNumber numberWithBool:!webviewIsTransparent] forKey:@"drawsBackground"];
    }
    
    [self.webview setNavigationDelegate:self];
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setBool:FALSE forKey:@"NSAutomaticQuoteSubstitutionEnabled"];
    
    // Mouse monitors
    [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskLeftMouseDown handler:^NSEvent * _Nullable(NSEvent * _Nonnull event) {
        id window = [event window];
        if (window == self.mainWindow) {
            self.mouseEvent = event;
        }
        return event;
    }];
    
    [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskLeftMouseUp handler:^NSEvent * _Nullable(NSEvent * _Nonnull event) {
        id window = [event window];
        if (window == self.mainWindow) {
            self.mouseEvent = nil;
            [self ShowMouse];
        }
        return event;
    }];
    
    self.applicationMenu = [NSMenu new];
    
}

- (NSMenuItem*) newMenuItem :(NSString*)title :(SEL)selector :(NSString*)key :(NSEventModifierFlags)flags {
    NSMenuItem *result = [[[NSMenuItem alloc] initWithTitle:title action:selector keyEquivalent:key] autorelease];
    if( flags != 0 ) {
        [result setKeyEquivalentModifierMask:flags];
    }
    return result;
}

- (NSMenuItem*) newMenuItem :(NSString*)title :(SEL)selector :(NSString*)key  {
    return [self newMenuItem :title :selector :key :0];
}

- (NSMenu*) newMenu :(NSString*)title {
    WailsMenu *result = [[WailsMenu new] initWithTitle:title];
    [result setAutoenablesItems:NO];
    return result;
}

- (void) Quit {
    processMessage("Q");
}

- (void) loadRequest :(NSString*)url {
    NSURL *wkUrl = [NSURL URLWithString:url];
    NSURLRequest *wkRequest = [NSURLRequest requestWithURL:wkUrl];
    [self.webview loadRequest:wkRequest];
}

- (void) SetRGBA:(int)r :(int)g :(int)b :(int)a {
    float red = r/255.0;
    float green = g/255.0;
    float blue = b/255.0;
    float alpha = a/255.0;
    
    id colour = [NSColor colorWithCalibratedRed:red green:green blue:blue alpha:alpha ];
    
    [self.mainWindow setBackgroundColor:colour];
}

- (void) HideMouse {
    [NSCursor hide];
}

- (void) ShowMouse {
    [NSCursor unhide];
}

- (bool) isFullScreen {
    long mask = [self.mainWindow styleMask];
    return (mask & NSWindowStyleMaskFullScreen) == NSWindowStyleMaskFullScreen;
}

- (bool) isMaximised {
    long mask = [self.mainWindow styleMask];
    return (mask & NSWindowStyleMaskFullScreen) == NSWindowStyleMaskFullScreen;
}

// Fullscreen sets the main window to be fullscreen
- (void) Fullscreen {
    if( ! [self isFullScreen] ) {
        [self.mainWindow disableWindowConstraints];
        [self.mainWindow toggleFullScreen:nil];
    }
}

// UnFullscreen resets the main window after a fullscreen
- (void) UnFullscreen {
    if( [self isFullScreen] ) {
        [self.mainWindow applyWindowConstraints];
        [self.mainWindow toggleFullScreen:nil];
    }
}

- (void) Minimise {
    [self.mainWindow miniaturize:nil];
}

- (void) UnMinimise {
    [self.mainWindow deminiaturize:nil];
}

- (void) Hide {
    [self.mainWindow orderOut:nil];
}

- (void) Show {
    [self.mainWindow makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
}

- (void) Maximise {
    if (![self.mainWindow isZoomed]) {
        [self.mainWindow zoom:nil];
    }
}

- (void) UnMaximise {
    if ([self.mainWindow isZoomed]) {
        [self.mainWindow zoom:nil];
    }
}

- (void) ExecJS:(NSString*)script {
   [self.webview evaluateJavaScript:script completionHandler:nil];
}

- (void) processURLResponse:(NSString *)url :(int)statusCode :(NSString *)contentType :(NSData *)data {
    id<WKURLSchemeTask> urlSchemeTask = self.urlRequests[url];
    NSURL *nsurl = [NSURL URLWithString:url];
    NSMutableDictionary *headerFields = [NSMutableDictionary new];
    if ( ![contentType isEqualToString:@""] ) {
        headerFields[@"content-type"] = contentType;
    }
    NSHTTPURLResponse *response = [[NSHTTPURLResponse new] initWithURL:nsurl statusCode:statusCode HTTPVersion:@"HTTP/1.1" headerFields:headerFields];
    [urlSchemeTask didReceiveResponse:response];
    [urlSchemeTask didReceiveData:data];
    [urlSchemeTask didFinish];
    [self.urlRequests removeObjectForKey:url];
    [response release];
    [headerFields release];
}

- (void)webView:(nonnull WKWebView *)webView startURLSchemeTask:(nonnull id<WKURLSchemeTask>)urlSchemeTask {
    // Do something
    self.urlRequests[urlSchemeTask.request.URL.absoluteString] = urlSchemeTask;
    processURLRequest(self, [urlSchemeTask.request.URL.absoluteString UTF8String]);
}

- (void)webView:(nonnull WKWebView *)webView stopURLSchemeTask:(nonnull id<WKURLSchemeTask>)urlSchemeTask {
    
}

- (void)webView:(WKWebView *)webView didFinishNavigation:(WKNavigation *)navigation {
    processMessage("DomReady");
}

- (void)userContentController:(nonnull WKUserContentController *)userContentController didReceiveScriptMessage:(nonnull WKScriptMessage *)message {
    NSString *m = message.body;
    
    // Check for drag
    if ( [m isEqualToString:@"drag"] ) {
        if( [self isFullScreen] ) {
            return;
        }
        if( self.mouseEvent != nil ) {
           [self.mainWindow performWindowDragWithEvent:self.mouseEvent];
        }
        return;
    }
    
    const char *_m = [m UTF8String];
    
    processMessage(_m);
}


/***** Dialogs ******/
-(void) MessageDialog :(NSString*)dialogType :(NSString*)title :(NSString*)message :(NSString*)button1 :(NSString*)button2 :(NSString*)button3 :(NSString*)button4 :(NSString*)defaultButton :(NSString*)cancelButton :(void*)iconData :(int)iconDataLength {

    WailsAlert *alert = [WailsAlert new];
    
    int style = NSAlertStyleInformational;
    if (dialogType != nil ) {
        if( [dialogType isEqualToString:@"warning"] ) {
            style = NSAlertStyleWarning;
        }
        if( [dialogType isEqualToString:@"error"] ) {
            style = NSAlertStyleCritical;
        }
    }
    [alert setAlertStyle:style];
    if( title != nil ) {
        [alert setMessageText:title];
    }
    if( message != nil ) {
        [alert setInformativeText:message];
    }
    
    [alert addButton:button1 :defaultButton :cancelButton];
    [alert addButton:button2 :defaultButton :cancelButton];
    [alert addButton:button3 :defaultButton :cancelButton];
    [alert addButton:button4 :defaultButton :cancelButton];
    
    NSImage *icon = nil;
    if (iconData != nil) {
        NSData *imageData = [NSData dataWithBytes:iconData length:iconDataLength];
        icon = [[NSImage alloc] initWithData:imageData];
    }
    if( icon != nil) {
       [alert setIcon:icon];
    }
    [alert.window setLevel:NSFloatingWindowLevel];

    long response = [alert runModal];
    int result;

    if( response == NSAlertFirstButtonReturn ) {
        result = 0;
    }
    else if( response == NSAlertSecondButtonReturn ) {
        result = 1;
    }
    else if( response == NSAlertThirdButtonReturn ) {
        result = 2;
    } else {
        result = 3;
    }
    processMessageDialogResponse(result);
}

-(void) OpenFileDialog :(NSString*)title :(NSString*)defaultFilename :(NSString*)defaultDirectory :(bool)allowDirectories :(bool)allowFiles :(bool)canCreateDirectories :(bool)treatPackagesAsDirectories :(bool)resolveAliases :(bool)showHiddenFiles :(bool)allowMultipleSelection :(NSString*)filters {
    
    
    // Create the dialog
    NSOpenPanel *dialog = [NSOpenPanel openPanel];

    // Valid but appears to do nothing.... :/
    if( title != nil ) {
        [dialog setTitle:title];
    }

    // Filters - semicolon delimited list of file extensions
    if( allowFiles ) {
        if( filters != nil && [filters length] > 0) {
            filters = [filters stringByReplacingOccurrencesOfString:@"*." withString:@""];
            filters = [filters stringByReplacingOccurrencesOfString:@" " withString:@""];
            NSArray *filterList = [filters componentsSeparatedByString:@";"];
            if (@available(macOS 10.16, *)) {
                NSMutableArray *contentTypes = [[NSMutableArray new] autorelease];
                for (NSString *filter in filterList) {
                    UTType *t = [UTType typeWithFilenameExtension:filter];
                    [contentTypes addObject:t];
                }
                [dialog setAllowedContentTypes:contentTypes];
            } else {
                [dialog setAllowedFileTypes:filterList];
            }
        } else {
            [dialog setAllowsOtherFileTypes:true];
        }
        // Default Filename
        if( defaultFilename != nil ) {
            [dialog setNameFieldStringValue:defaultFilename];
        }
        
        [dialog setAllowsMultipleSelection: allowMultipleSelection];
        [dialog setShowsHiddenFiles: showHiddenFiles];

    }

    // Default Directory
    if( defaultDirectory != nil ) {
        NSURL *url = [NSURL fileURLWithPath:defaultDirectory];
        [dialog setDirectoryURL:url];
    }


    // Setup Options
    [dialog setCanChooseFiles: allowFiles];
    [dialog setCanChooseDirectories: allowDirectories];
    [dialog setCanCreateDirectories: canCreateDirectories];
    [dialog setResolvesAliases: resolveAliases];
    [dialog setTreatsFilePackagesAsDirectories: treatPackagesAsDirectories];

    // Setup callback handler
    [dialog beginSheetModalForWindow:self.mainWindow completionHandler:^(NSModalResponse returnCode) {
        NSMutableArray *arr = [NSMutableArray new];
        for (NSURL *url in [dialog URLs]) {
            [arr addObject:[url path]];
        }
        NSData *jsonData = [NSJSONSerialization dataWithJSONObject:arr options:0 error:nil];
        NSString *nsjson = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        processOpenFileDialogResponse([nsjson UTF8String]);
        [nsjson release];
        [arr release];
    }];
    
}


-(void) SaveFileDialog :(NSString*)title :(NSString*)defaultFilename :(NSString*)defaultDirectory :(bool)canCreateDirectories :(bool)treatPackagesAsDirectories :(bool)showHiddenFiles :(NSString*)filters; {
    
    
    // Create the dialog
    NSSavePanel *dialog = [NSOpenPanel savePanel];

    // Valid but appears to do nothing.... :/
    if( title != nil ) {
        [dialog setTitle:title];
    }

    // Filters - semicolon delimited list of file extensions
    if( filters != nil ) {
        filters = [filters stringByReplacingOccurrencesOfString:@"*." withString:@""];
        filters = [filters stringByReplacingOccurrencesOfString:@" " withString:@""];
        NSArray *filterList = [filters componentsSeparatedByString:@";"];
        [dialog setAllowedFileTypes:filterList];
    } else {
        [dialog setAllowsOtherFileTypes:true];
    }
    // Default Filename
    if( defaultFilename != nil ) {
        [dialog setNameFieldStringValue:defaultFilename];
    }
    
    // Default Directory
    if( defaultDirectory != nil ) {
        NSURL *url = [NSURL fileURLWithPath:defaultDirectory];
        [dialog setDirectoryURL:url];
    }

    // Setup Options
    [dialog setCanCreateDirectories: canCreateDirectories];
    [dialog setTreatsFilePackagesAsDirectories: treatPackagesAsDirectories];
    [dialog setShowsHiddenFiles: showHiddenFiles];

    // Setup callback handler
    [dialog beginSheetModalForWindow:self.mainWindow completionHandler:^(NSModalResponse returnCode) {
        NSURL *url = [dialog URL];
        if ( url != nil ) {
            processSaveFileDialogResponse([url.path UTF8String]);
            return;
        }
        processSaveFileDialogResponse("");
    }];
        
}

- (void) SetAbout :(NSString*)title :(NSString*)description :(void*)imagedata :(int)datalen {
    self.aboutTitle = title;
    self.aboutDescription = description;
   
    NSData *imageData = [NSData dataWithBytes:imagedata length:datalen];
    self.aboutImage = [[NSImage alloc] initWithData:imageData];
}

-(void) About {
    
    WailsAlert *alert = [WailsAlert new];
    [alert setAlertStyle:NSAlertStyleInformational];
    if( self.aboutTitle != nil ) {
        [alert setMessageText:self.aboutTitle];
    }
    if( self.aboutDescription != nil ) {
        [alert setInformativeText:self.aboutDescription];
    }
    
    
    [alert.window setLevel:NSFloatingWindowLevel];
    if ( self.aboutImage != nil) {
        [alert setIcon:self.aboutImage];
    }

    [alert runModal];
}

@end

