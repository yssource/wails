package process

import (
	"context"
	"os"
	"os/exec"

	"github.com/wailsapp/wails/v2/pkg/clilogger"
)

// Process defines a process that can be executed
type Process struct {
	logger  *clilogger.CLILogger
	cmd     *exec.Cmd
	running bool
}

// NewProcess creates a new process struct
func NewProcess(ctx context.Context, logger *clilogger.CLILogger, cmd string, args ...string) *Process {
	result := &Process{
		logger: logger,
		cmd:    exec.CommandContext(ctx, cmd, args...),
	}
	result.cmd.Stdout = os.Stdout
	result.cmd.Stderr = os.Stderr
	return result
}

// Start the process
func (p *Process) Start() error {

	err := p.cmd.Start()
	if err != nil {
		return err
	}

	p.running = true

	go func(p *Process) {
		p.logger.Println("Starting process (PID: %d)", p.cmd.Process.Pid)
		err := p.cmd.Wait()
		if err != nil {
			p.running = false
			p.logger.Println("Process failed to run: %s", err.Error())
			return
		}
		p.logger.Println("Exiting process (PID: %d)", p.cmd.Process.Pid)
	}(p)

	return nil
}

// Kill the process
func (p *Process) Kill() error {
	if p.running {
		println("Calling kill")
		p.running = false
		return p.cmd.Process.Kill()
	}
	return nil
}

// PID returns the process PID
func (p *Process) PID() int {
	return p.cmd.Process.Pid
}
