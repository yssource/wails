package webview

import "C"

// DialogType is an enumeration of all supported system dialog types
type DialogType int

const (
	// DialogTypeOpen is a system file open dialog
	DialogTypeOpen DialogType = iota
	// DialogTypeSave is a system file save dialog
	DialogTypeSave
	// DialogTypeAlert is a system alert dialog (message box)
	DialogTypeAlert
)

// WebView is our webview interface
type WebView interface {
	// Run() starts the main UI loop until the user closes the webview window or
	// Terminate() is called.
	Run()
	// Loop() runs a single iteration of the main UI.
	Loop(blocking bool) bool
	// SetTitle() changes window title. This method must be called from the main
	// thread only. See Dispatch() for more details.
	SetTitle(title string)
	// SetFullscreen() controls window full-screen mode. This method must be
	// called from the main thread only. See Dispatch() for more details.
	SetFullscreen(fullscreen bool)
	// SetColor() changes window background color. This method must be called from
	// the main thread only. See Dispatch() for more details.
	SetColor(r, g, b, a uint8)
	// Eval() evaluates an arbitrary JS code inside the webview. This method must
	// be called from the main thread only. See Dispatch() for more details.
	Eval(js string) error
	// InjectJS() injects an arbitrary block of CSS code using the JS API. This
	// method must be called from the main thread only. See Dispatch() for more
	// details.
	InjectCSS(css string)
	// Dialog() opens a system dialog of the given type and title. String
	// argument can be provided for certain dialogs, such as alert boxes. For
	// alert boxes argument is a message inside the dialog box.
	Dialog(dlgType DialogType, flags int, title string, arg string, filter string) string
	// Terminate() breaks the main UI loop. This method must be called from the main thread
	// only. See Dispatch() for more details.
	Terminate()
	// Dispatch() schedules some arbitrary function to be executed on the main UI
	// thread. This may be helpful if you want to run some JavaScript from
	// background threads/goroutines, or to terminate the app.
	Dispatch(func())
	// Exit() closes the window and cleans up the resources. Use Terminate() to
	// forcefully break out of the main UI loop.
	Exit()
}

type ExternalInvokeCallbackFunc func(w WebView, data string)

type Settings struct {
	// WebView main window title
	Title string
	// URL to open in a webview
	URL string
	// Window width in pixels
	Width int
	// Window height in pixels
	Height int
	// Allows/disallows window resizing
	Resizable bool
	// Enable debugging tools (Linux/BSD/MacOS, on Windows use Firebug)
	Debug bool
	// A callback that is executed when JavaScript calls "window.external.invoke()"
	ExternalInvokeCallback ExternalInvokeCallbackFunc
}
