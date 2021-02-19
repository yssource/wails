package dev

import (
	"context"
	"fmt"
	"io"
	"os"
	"os/signal"
	"runtime"
	"strings"
	"syscall"
	"time"

	"github.com/wailsapp/wails/v2/pkg/commands/build"

	"github.com/wailsapp/wails/v2/internal/process"

	"github.com/wzshiming/ctc"

	"github.com/wailsapp/wails/v2/internal/fs"

	"github.com/fsnotify/fsnotify"

	"github.com/leaanthony/clir"
	"github.com/wailsapp/wails/v2/pkg/clilogger"
)

// AddSubcommand adds the `dev` command for the Wails application
func AddSubcommand(app *clir.Cli, w io.Writer) error {

	command := app.NewSubCommand("dev", "Development mode")

	// Passthrough ldflags
	ldflags := ""
	command.StringFlag("ldflags", "optional ldflags", &ldflags)

	// compiler command
	compilerCommand := "go"
	command.StringFlag("compiler", "Use a different go compiler to build, eg go1.15beta1", &compilerCommand)

	// extensions to trigger rebuilds
	extensions := "go"
	command.StringFlag("e", "Extensions to trigger rebuilds (comma separated) eg go,js,css,html", &extensions)

	command.Action(func() error {

		// Create logger
		logger := clilogger.New(w)
		app.PrintBanner()

		// TODO: Check you are in a project directory
		var extensionsThatTriggerARebuild = strings.Split(extensions, ",")

		reloader, err := NewReloader(logger, extensionsThatTriggerARebuild, ldflags, compilerCommand)
		if err != nil {
			return err
		}

		// Start
		err = reloader.Start()
		if err != nil {
			println("ERRRRRRRRRR: %+v", err)
		}

		logger.Println("\nDevelopment mode exited")

		return err
	})

	return nil
}

type Reloader struct {

	// Main context
	ctx context.Context

	// Signal context
	signalContext context.Context

	// notify
	watcher *fsnotify.Watcher

	// Logger
	logger *clilogger.CLILogger

	// Extensions to listen for
	extensionsThatTriggerARebuild []string

	// The binary we are running
	binary *process.Process

	// options
	ldflags  string
	compiler string
}

func NewReloader(logger *clilogger.CLILogger, extensionsThatTriggerARebuild []string, ldFlags string, compiler string) (*Reloader, error) {
	var result Reloader

	// Create context
	result.ctx = context.Background()

	// Signal context (we don't need cancel)
	signalContext, _ := signal.NotifyContext(result.ctx, os.Interrupt, os.Kill, syscall.SIGTERM)
	result.signalContext = signalContext

	// Create watcher
	watcher, err := fsnotify.NewWatcher()
	if err != nil {
		return nil, err
	}
	result.watcher = watcher

	// Logger
	result.logger = logger

	// Extensions
	result.extensionsThatTriggerARebuild = extensionsThatTriggerARebuild

	// Options
	result.ldflags = ldFlags
	result.compiler = compiler

	return &result, nil
}

func (r *Reloader) Start() error {

	err := r.rebuildBinary()
	if err != nil {
		return err
	}

	// Get project dir
	dir, err := os.Getwd()
	if err != nil {
		return err
	}

	// Get all subdirectories
	dirs, err := fs.GetSubdirectories(dir)
	if err != nil {
		return err
	}

	// Setup a watcher for non-node_modules directories
	r.logger.Println("Watching (sub)directories: %s", dir)

	dirs.Each(func(dir string) {
		if strings.Contains(dir, "node_modules") {
			return
		}
		err = r.watcher.Add(dir)
		if err != nil {
			r.logger.Fatal(err.Error())
		}
	})

	// Main loop
	for {
		select {
		case <-r.signalContext.Done():
			if r.binary != nil {
				println("Binary is not nil - kill")
				return r.binary.Kill()
			}
			return nil
		case event := <-r.watcher.Events:
			err := r.processWatcherEvent(event)
			if err != nil {
				println("error from processWatcherEvent. Calling cancel()")
				println("Calling kill")
				return r.binary.Kill()
			}
		}
	}
}

func (r *Reloader) processWatcherEvent(event fsnotify.Event) error {

	// Check for new directories
	if event.Op&fsnotify.Create == fsnotify.Create {
		// If this is a folder, add it to our watch list
		if fs.DirExists(event.Name) {
			if !strings.Contains(event.Name, "node_modules") {
				err := r.watcher.Add(event.Name)
				if err != nil {
					return err
				}
				r.logger.Println("Watching directory: %s", event.Name)
			}
		}
		return nil
	}

	// Check for file writes
	if event.Op&fsnotify.Write == fsnotify.Write {

		var rebuild bool

		// Iterate all file patterns
		for _, pattern := range r.extensionsThatTriggerARebuild {
			if strings.HasSuffix(event.Name, pattern) {
				rebuild = true
			}
		}

		if !rebuild {
			return nil
		}

		r.logger.Println("\n%s[Build triggered] %s %s", ctc.ForegroundGreen|ctc.ForegroundBright, event.Name, ctc.Reset)

		return r.rebuildBinary()
	}
	return nil
}

func (r *Reloader) rebuildBinary() error {

	// rebuild binary
	binary, err := r.buildApp()
	if err != nil {
		return err
	}

	// Kill current binary if running
	if r.binary != nil {
		err = r.binary.Kill()
		if err != nil {
			return err
		}
	}

	newProcess := process.NewProcess(r.ctx, r.logger, binary)
	err = newProcess.Start()
	if err != nil {
		return err
	}

	// Ensure process runs correctly

	return nil
}

//func restartApp(logger *clilogger.CLILogger, outputType string, ldflags string, compilerCommand string, debugBinaryProcess *process.Process) (*process.Process, error) {
//
//	appBinary, err := buildApp(logger, outputType, ldflags, compilerCommand)
//	println()
//	if err != nil {
//		logger.Fatal(err.Error())
//		return nil, errors.Wrap(err, "Build Failed:")
//	}
//	logger.Println("Build new binary: %s", appBinary)
//
//	// Kill existing binary if need be
//	if debugBinaryProcess != nil {
//		killError := debugBinaryProcess.Kill()
//
//		if killError != nil {
//			logger.Fatal("Unable to kill debug binary (PID: %d)!", debugBinaryProcess.PID())
//		}
//
//		debugBinaryProcess = nil
//	}
//
//	// TODO: Generate `backend.js`
//
//	// Start up new binary
//	newProcess := process.NewProcess(logger, appBinary)
//	err = newProcess.Start()
//	if err != nil {
//		// Remove binary
//		deleteError := fs.DeleteFile(appBinary)
//		if deleteError != nil {
//			logger.Fatal("Unable to delete app binary: " + appBinary)
//		}
//		logger.Fatal("Unable to start application: %s", err.Error())
//	}
//
//	// Check if port is open
//	timeout := time.Second
//	conn, err := net.DialTimeout("tcp", net.JoinHostPort("host", port), timeout)
//	if err != nil {
//		return
//	}
//	newProcess.Running
//	return newProcess, nil
//}

// buildapp attempts to compile the application
// It returns the path to the new binary or an error
func (r *Reloader) buildApp() (string, error) {

	// Create random output file
	outputFile := fmt.Sprintf("debug-%d", time.Now().Unix())

	// Create BuildOptions
	buildOptions := &build.Options{
		Logger:         r.logger,
		OutputType:     "dev",
		Mode:           build.Debug,
		Pack:           false,
		Platform:       runtime.GOOS,
		LDFlags:        r.ldflags,
		Compiler:       r.compiler,
		OutputFile:     outputFile,
		IgnoreFrontend: true,
	}

	return build.Build(buildOptions)

}
