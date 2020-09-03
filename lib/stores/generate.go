// Package stores
package stores

import "os"

// Generate stores that are found in the project
func Generate() error {
	cwd, err := os.Getwd()
	if err != nil {
		return err
	}
	ParseProject(cwd)
	return nil
}
