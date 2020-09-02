package message

import "fmt"

// windowMessageParser does what it says on the tin!
func windowMessageParser(message string) (*parsedMessage, error) {

	// Sanity check: Window messages must be at least 2 bytes
	if len(message) < 2 {
		return nil, fmt.Errorf("window message was an invalid length")
	}

	// Extract event type
	windowEvent := message[1]
	parsedMessage := &parsedMessage{}

	// Switch the windowEvent type
	switch windowEvent {

	// Closed window
	case 'C':
		parsedMessage.Topic = "quit"
		parsedMessage.Data = "Window Closed"

	// Unknown event type
	default:
		return nil, fmt.Errorf("unknown message: %s", message)
	}

	return parsedMessage, nil
}
