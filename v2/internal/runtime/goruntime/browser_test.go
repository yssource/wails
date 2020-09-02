package goruntime

import (
	"os"
	"testing"

	"github.com/leaanthony/wailsv2/v2/internal/logger"
	"github.com/leaanthony/wailsv2/v2/internal/servicebus"
)

func TestBrowserOpen(t *testing.T) {
	mylogger := logger.New(os.Stdout)
	myServiceBus := servicebus.New(mylogger)
	myRuntime := New(myServiceBus)
	myRuntime.Browser.Open("http://www.google.com")
}
