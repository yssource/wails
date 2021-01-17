package menumanager

import (
	"fmt"
	"github.com/wailsapp/wails/v2/internal/counter"
	"github.com/wailsapp/wails/v2/pkg/menu"
)

type Manager struct {

	// MenuItemMap is a map of all menu items against a generated ID
	menuItemMap        map[string]*menu.MenuItem
	menuItemIDCounter  *counter.Counter
	processedMenuItems map[*menu.MenuItem]*ProcessedMenuItem

	// Map wails menus to internal menus
	trayMenuMap       map[*menu.TrayMenu]*TrayMenu
	trayMenuIDCounter *counter.Counter
}

func NewManager() *Manager {
	return &Manager{
		trayMenuMap:        make(map[*menu.TrayMenu]*TrayMenu),
		trayMenuIDCounter:  counter.NewCounter(0),
		menuItemMap:        make(map[string]*menu.MenuItem),
		menuItemIDCounter:  counter.NewCounter(0),
		processedMenuItems: make(map[*menu.MenuItem]*ProcessedMenuItem),
	}
}

func (m *Manager) ProcessClick(menuID string, data string) error {
	// Get item from callback map
	menuItem := m.menuItemMap[menuID]
	if menuItem == nil {
		return fmt.Errorf("menuItem doesn't exist")
	}

	if menuItem.Click == nil {
		return fmt.Errorf("menuItem 'does not have a callback")
	}

	callbackData := &menu.CallbackData{
		MenuItem:    menuItem,
		ContextData: data,
	}

	// Callback!
	go menuItem.Click(callbackData)
	return nil
}
