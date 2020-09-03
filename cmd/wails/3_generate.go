package main

import (
	"fmt"

	"github.com/leaanthony/spinner"
	"github.com/wailsapp/wails/lib/stores"
)

func init() {

	var generateStores = false

	buildSpinner := spinner.NewSpinner()
	buildSpinner.SetSpinSpeed(50)

	commandDescription := `This command will generate components`
	generateCommand := app.Command("generate", "Generate components").
		LongDescription(commandDescription).
		BoolFlag("s", "Generate Stores", &generateStores)

	generateCommand.Action(func() error {

		logger.PrintSmallBanner("Generating")
		fmt.Println()

		if generateStores {
			err := stores.Generate()
			if err != nil {
				return err
			}
		}

		return nil

	})
}
