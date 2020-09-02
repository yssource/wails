package goruntime

import (
	"fmt"

	"github.com/leaanthony/wailsv2/v2/internal/crypto"
	"github.com/leaanthony/wailsv2/v2/internal/servicebus"
)

// Dialog defines all Dialog related operations
type Dialog interface {
	SaveFile(title string) string
	SelectFile(title string) string
	SelectDirectory(title string) string
}

// dialog exposes the Dialog interface
type dialog struct {
	bus *servicebus.ServiceBus
}

// newDialogs creates a new Dialogs struct
func newDialog(bus *servicebus.ServiceBus) Dialog {
	return &dialog{
		bus: bus,
	}
}

// SelectFile prompts the user to select a file
func (r *dialog) SelectFile(title string) string {

	// Create unique dialog callback
	uniqueCallback := crypto.RandomID()

	// Subscribe to the respose channel
	responseTopic := "dialog:fileselected:" + uniqueCallback
	dialogResponseChannel, err := r.bus.Subscribe(responseTopic)
	if err != nil {
		fmt.Printf("ERROR: Cannot subscribe to bus topic: %+v\n", err.Error())
	}

	// Publish dialog request
	// TODO: Add title to request
	r.bus.Publish("dialog:select:file:"+title, responseTopic)

	// Wait for result
	result := <-dialogResponseChannel

	// Delete subscription to response topic
	r.bus.UnSubscribe(responseTopic)

	return result.Data().(string)
}

// SaveFile prompts the user to select a file to save to
func (r *dialog) SaveFile(title string) string {

	// Create unique dialog callback
	uniqueCallback := crypto.RandomID()

	// Subscribe to the respose channel
	responseTopic := "dialog:filesaveselected:" + uniqueCallback
	dialogResponseChannel, err := r.bus.Subscribe(responseTopic)
	if err != nil {
		fmt.Printf("ERROR: Cannot subscribe to bus topic: %+v\n", err.Error())
	}

	// Publish dialog request
	// TODO: Add title to request
	r.bus.Publish("dialog:select:filesave:"+title, responseTopic)

	// Wait for result
	result := <-dialogResponseChannel

	// Delete subscription to response topic
	r.bus.UnSubscribe(responseTopic)

	return result.Data().(string)
}

// SelectDirectory prompts the user to select a file
func (r *dialog) SelectDirectory(title string) string {

	// Create unique dialog callback
	uniqueCallback := crypto.RandomID()

	// Subscribe to the respose channel
	responseTopic := "dialog:directoryselected:" + uniqueCallback
	dialogResponseChannel, err := r.bus.Subscribe(responseTopic)
	if err != nil {
		fmt.Printf("ERROR: Cannot subscribe to bus topic: %+v\n", err.Error())
	}

	// Publish dialog request
	// TODO: Add title to request
	r.bus.Publish("dialog:select:directory:"+title, responseTopic)

	// Wait for result
	var result *servicebus.Message = <-dialogResponseChannel

	// Delete subscription to response topic
	r.bus.UnSubscribe(responseTopic)

	return result.Data().(string)
}
