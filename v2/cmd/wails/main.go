package main

import (
	"fmt"
	"os"

	"github.com/wzshiming/ctc"

	"github.com/wailsapp/wails/v2/cmd/wails/internal/commands/update"

	"github.com/leaanthony/clir"
	"github.com/wailsapp/wails/v2/cmd/wails/internal/commands/build"
	"github.com/wailsapp/wails/v2/cmd/wails/internal/commands/debug"
	"github.com/wailsapp/wails/v2/cmd/wails/internal/commands/dev"
	"github.com/wailsapp/wails/v2/cmd/wails/internal/commands/doctor"
	"github.com/wailsapp/wails/v2/cmd/wails/internal/commands/generate"
	"github.com/wailsapp/wails/v2/cmd/wails/internal/commands/initialise"
)

func fatal(message string) {
	println(message)
	os.Exit(1)
}

func col(colour ctc.Color, text string) string {
	return fmt.Sprintf("%s%s%s", colour, text, ctc.Reset)
}

func Yellow(str string) string {
	return col(ctc.ForegroundBrightYellow, str)
}

func Red(str string) string {
	return col(ctc.ForegroundBrightRed, str)
}

func banner(cli *clir.Cli) string {
	return fmt.Sprintf("%s %s - Go/HTML Application Framework", Yellow("Wails"), Red(version))
}

func main() {

	var err error

	app := clir.NewCli("Wails", "Go/HTML Application Framework", version)

	app.SetBannerFunction(banner)

	build.AddBuildSubcommand(app, os.Stdout)
	err = initialise.AddSubcommand(app, os.Stdout)
	if err != nil {
		fatal(err.Error())
	}

	err = debug.AddSubcommand(app, os.Stdout)
	if err != nil {
		fatal(err.Error())
	}
	err = doctor.AddSubcommand(app, os.Stdout)
	if err != nil {
		fatal(err.Error())
	}

	err = dev.AddSubcommand(app, os.Stdout)
	if err != nil {
		fatal(err.Error())
	}

	err = generate.AddSubcommand(app, os.Stdout)
	if err != nil {
		fatal(err.Error())
	}

	err = update.AddSubcommand(app, os.Stdout, version)
	if err != nil {
		fatal(err.Error())
	}

	err = app.Run()
	if err != nil {
		println("\n\nERROR: " + err.Error())
	}
}
