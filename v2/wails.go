package wails

import (
	"github.com/leaanthony/wailsv2/v2/internal/app"
	"github.com/leaanthony/wailsv2/v2/internal/runtime/goruntime"
)

// Runtime is an alias for the goruntime.Runtime struct
type Runtime = goruntime.Runtime

// Options is an alias for the app.Options struct
type Options = app.Options

// CreateAppWithOptions creates an application based on the given config
func CreateAppWithOptions(options *Options) *app.App {
	return app.CreateApp(options)
}

// CreateApp creates an application based on the given title, width and height
func CreateApp(title string, width int, height int) *app.App {

	options := &app.Options{
		Title:  title,
		Width:  width,
		Height: height,
	}

	return app.CreateApp(options)
}
