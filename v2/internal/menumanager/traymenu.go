package menumanager

import (
	"encoding/json"
	"fmt"
	"github.com/wailsapp/wails/v2/pkg/menu"
)

type TrayMenu struct {
	ID    string         `json:"I"`
	Label string         `json:"l,omitempty"`
	Icon  string         `json:"i,omitempty"`
	Menu  *ProcessedMenu `json:"m,omitempty"`
}

func (t *TrayMenu) AsJSON() (string, error) {
	data, err := json.Marshal(t)
	if err != nil {
		return "", err
	}
	return string(data), nil
}

func (m *Manager) newTrayMenu(trayMenu *menu.TrayMenu) *TrayMenu {

	result := TrayMenu{
		ID:    m.generateTrayID(),
		Label: trayMenu.Label,
		Icon:  trayMenu.Icon,
		Menu:  m.ProcessMenu(trayMenu.Menu),
	}

	return &result
}

func (m *Manager) AddTrayMenu(trayMenu *menu.TrayMenu) *TrayMenu {

	result := m.newTrayMenu(trayMenu)

	// Add to map
	m.trayMenuMap[trayMenu] = result

	return result
}

func (m *Manager) generateTrayID() string {
	return fmt.Sprintf("T%d", m.trayMenuIDCounter.Increment())
}

func (m *Manager) GetTrayMenus() ([]*TrayMenu, error) {
	var result []*TrayMenu
	for _, trayMenu := range m.trayMenuMap {
		result = append(result, trayMenu)
	}

	return result, nil
}

func (m *Manager) GetTrayMenusAsJSON() ([]string, error) {
	var result []string
	for _, trayMenu := range m.trayMenuMap {
		JSON, err := trayMenu.AsJSON()
		if err != nil {
			return nil, err
		}
		result = append(result, JSON)
	}

	return result, nil
}

// SetTrayMenu updates or creates a menu
func (m *Manager) SetTrayMenu(trayMenu *menu.TrayMenu) (string, error) {
	return "", nil
}

func (m *Manager) UpdateTrayMenuLabel(trayMenu *menu.TrayMenu) (string, error) {
	return "", nil
}
