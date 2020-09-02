package goruntime

import "github.com/leaanthony/wailsv2/v2/internal/servicebus"

// Window defines all Window related operations
type Window interface {
	Close()
	SetTitle(title string)
	Fullscreen()
	UnFullscreen()
	SetColour(colour string)
}

// Window exposes the Windows interface
type window struct {
	bus *servicebus.ServiceBus
}

// newWindow creates a new window struct
func newWindow(bus *servicebus.ServiceBus) Window {
	return &window{
		bus: bus,
	}
}

// Close the Window
// DISCUSSION:
//   Should we even be doing this now we have a server build?
//   Runtime.Quit() makes more sense than closing a window...
func (w *window) Close() {
	w.bus.Publish("quit", "runtime.Close()")
}

// SetTitle sets the title of the window
func (w *window) SetTitle(title string) {
	w.bus.Publish("window:settitle", title)
}

// Fullscreen makes the window fullscreen
func (w *window) Fullscreen() {
	w.bus.Publish("window:fullscreen", "")
}

// UnFullscreen makes the window UnFullscreen
func (w *window) UnFullscreen() {
	w.bus.Publish("window:unfullscreen", "")
}

// SetColour sets the window colour to the given string
func (w *window) SetColour(colour string) {
	w.bus.Publish("window:setcolour", colour)
}
