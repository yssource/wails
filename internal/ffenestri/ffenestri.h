#ifndef __FFENESTRI_H__
#define __FFENESTRI_H__

#include <stdio.h>

extern void *NewApplication(const char *title, int width, int height, int resizable, int devtools, int fullscreen);
extern void SetMinWindowSize(void *app, int minWidth, int minHeight);
extern void SetMaxWindowSize(void *app, int maxWidth, int maxHeight);
extern void Run(void *app, int argc, char **argv);
extern void DestroyApplication(void *app);
extern void SetDebug(void *app, int flag);
extern void SetBindings(void *app, const char *bindings);
extern void ExecJS(void *app, const char *script);
extern void Quit(void *app);
extern void SetTitle(void *app, const char *title);
extern void Fullscreen(void *app);
extern void UnFullscreen(void *app);
extern int SetColour(void *app, const char *colourString);
extern void DisableFrame(void *app);
extern char *SaveFileDialogOnMainThread(void *appPointer, char *title);
extern char *OpenFileDialogOnMainThread(void *appPointer, char *title);
extern char *OpenDirectoryDialogOnMainThread(void *appPointer, char *title);

#endif
