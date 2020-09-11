package webview

/*
#include "webview_darwin.h"
*/
import "C"

import "unsafe"

const (
	// DialogFlagFile is a normal file picker dialog
	DialogFlagFile = C.WEBVIEW_DIALOG_FLAG_FILE
	// DialogFlagDirectory is an open directory dialog
	DialogFlagDirectory = C.WEBVIEW_DIALOG_FLAG_DIRECTORY
	// DialogFlagInfo is an info alert dialog
	DialogFlagInfo = C.WEBVIEW_DIALOG_FLAG_INFO
	// DialogFlagWarning is a warning alert dialog
	DialogFlagWarning = C.WEBVIEW_DIALOG_FLAG_WARNING
	// DialogFlagError is an error dialog
	DialogFlagError = C.WEBVIEW_DIALOG_FLAG_ERROR
)

type MacWebView struct {
	app unsafe.Pointer
}

func NewWebview(settings Settings) WebView {
	return &MacWebView{}
}

func (w *MacWebView) Dialog(dlgType DialogType, flags int, title string, arg string, filter string) string {
	// TBD
	return ""
}

func (w *MacWebView) Dispatch(func()) {
	// TBD
}

func (w *MacWebView) Eval(js string) error {
	// TBD
	return nil
}

func (w *MacWebView) Exit() {
	// TBD
}

func (w *MacWebView) Run() {}
func (w *MacWebView) Loop(blocking bool) bool {
	return true
}
func (w *MacWebView) SetTitle(title string)         {}
func (w *MacWebView) SetFullscreen(fullscreen bool) {}
func (w *MacWebView) SetColor(r, g, b, a uint8)     {}
func (w *MacWebView) InjectCSS(css string)          {}
func (w *MacWebView) Terminate()                    {}
