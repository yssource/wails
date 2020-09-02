package main

import (
	wails "github.com/wailsapp/wails/v2"
)

// RuntimeTest to test the runtimes
type RuntimeTest struct {
	runtime *wails.Runtime
}

// WailsInit is an initialisation method
func (r *RuntimeTest) WailsInit(runtime *wails.Runtime) error {
	r.runtime = runtime
	println("Woohoo I'm here!")

	// Set title!
	// runtime.Window.SetTitle("My App!")

	r.runtime.Events.On("testevent", func(optionalParams ...interface{}) {
		println("Wooohoooo! I got called!")
	})
	return nil
}

// WailsShutdown is called during shutdown
func (r *RuntimeTest) WailsShutdown() {
	// This is a test
	println("WOOOOOOOOOOOOOO WailsShutdown CALLED")
}

// EmitSingleEventNoParams will emit a single event with the given name and no params
func (r *RuntimeTest) EmitSingleEventNoParams(name string) {
	r.runtime.Events.Emit(name)
}

// EmitSingleEventWithOneParam will emit a single event with the given name
func (r *RuntimeTest) EmitSingleEventWithOneParam(name string) {
	r.runtime.Events.Emit(name, 1)
}

// RuntimeQuit will call the Runtime.Quit method
func (r *RuntimeTest) RuntimeQuit() {
	r.runtime.Quit()
}

// Fullscreen will call the Runtime.Fullscreen method
func (r *RuntimeTest) Fullscreen() {
	r.runtime.Window.Fullscreen()
}

// UnFullscreen will call the Runtime.UnFullscreen method
func (r *RuntimeTest) UnFullscreen() {
	r.runtime.Window.UnFullscreen()
}

// SetColour will call the Runtime.UnFullscreen method
func (r *RuntimeTest) SetColour(colour string) {
	r.runtime.Window.SetColour(colour)
}

// SelectFile will call the Runtime.Dialog.OpenFile method
func (r *RuntimeTest) SelectFile() string {
	return r.runtime.Dialog.SelectFile("Open File Title")
}

// SaveFile will call the Runtime.Dialog.SaveFile method
func (r *RuntimeTest) SaveFile() string {
	return r.runtime.Dialog.SaveFile("Save File Title")
}

// SelectDirectory will call the Runtime.Dialog.OpenDirectory method
func (r *RuntimeTest) SelectDirectory() string {
	return r.runtime.Dialog.SelectDirectory("Open Directory Title")
}
