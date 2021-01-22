package menumanager

import (
	"encoding/json"
	"fmt"
	"github.com/wailsapp/wails/v2/pkg/menu"
	"github.com/wailsapp/wails/v2/pkg/menu/keys"
)

type ProcessedMenu struct {
	ID string `json:"I"`

	Items       []*ProcessedMenuItem `json:"i,omitempty"`
	RadioGroups []*RadioGroup        `json:"r,omitempty"`
}

func (m *Manager) ProcessMenu(menu *menu.Menu) *ProcessedMenu {
	wm := m.NewWailsMenu(menu)

	if len(wm.Menu) == 0 {
		return nil
	}

	return &ProcessedMenu{
		ID:          m.generateMenuID(),
		Items:       wm.Menu,
		RadioGroups: wm.RadioGroups,
	}
}

type ProcessedMenuItem struct {
	// ID of the menu item
	ID string `json:"I"`

	// Label is what appears as the menu text
	Label string `json:"l,omitempty"`

	// AlternateLabel is a secondary label (Used by Mac)
	AlternateLabel string `json:"L,omitempty"`

	// Role is a predefined menu type
	Role menu.Role `json:"r,omitempty"`

	// Accelerator holds a representation of a key binding
	Accelerator *keys.Accelerator `json:"a,omitempty"`

	// Type of MenuItem, EG: Checkbox, Text, Separator, Radio, Submenu
	Type menu.Type `json:"t,omitempty"`

	// Font to use for the menu item
	Font string `json:"f,omitempty"`

	// Font to use for the menu item
	FontSize int `json:"F,omitempty"`

	// RGBA is the colour of the menu item
	RGBA string `json:"R,omitempty"`

	// Image is an image for the menu item (base64 string)
	Image string `json:"i,omitempty"`

	// Disabled makes the item unselectable
	Disabled *bool `json:"d,omitempty"`

	// Hidden ensures that the item is not shown in the menu
	Hidden *bool `json:"h,omitempty"`

	// Checked indicates if the item is selected (used by Checkbox and Radio types only)
	Checked *bool `json:"c,omitempty"`

	// Submenu contains a list of menu items that will be shown as a submenu
	//SubMenu []*MenuItem `json:"SubMenu,omitempty"`
	SubMenu []*ProcessedMenuItem `json:"s,omitempty"`

	// Indicates if this item has a callback
	HasCallback *bool `json:"C,omitempty"`
}

func (m *Manager) generateMenuItemID() string {
	return fmt.Sprintf("%d", m.menuItemIDCounter.Increment())
}

func (m *Manager) generateMenuID() string {
	return fmt.Sprintf("%d", m.menuIDCounter.Increment())
}

func (m *Manager) NewProcessedMenuItem(menuItem *menu.MenuItem) *ProcessedMenuItem {

	// Check if this menu has already been processed.
	// This is to prevent duplicates.
	existingMenuItem := m.processedMenuItems[menuItem]
	if existingMenuItem != nil {
		return &ProcessedMenuItem{ID: existingMenuItem.ID}
	}

	ID := m.generateMenuItemID()

	result := &ProcessedMenuItem{
		ID:             ID,
		Label:          menuItem.Label,
		AlternateLabel: menuItem.AlternateLabel,
		Role:           menuItem.Role,
		Accelerator:    menuItem.Accelerator,
		Type:           menuItem.Type,
		Font:           menuItem.Font,
		FontSize:       menuItem.FontSize,
		RGBA:           menuItem.RGBA,
		Image:          menuItem.Image,
		Disabled:       nil,
		Hidden:         nil,
		Checked:        nil,
		SubMenu:        nil,
		HasCallback:    nil,
	}

	if menuItem.Hidden {
		result.Hidden = new(bool)
		*result.Hidden = true
	}

	if menuItem.Disabled {
		result.Disabled = new(bool)
		*result.Disabled = true
	}

	if menuItem.Checked {
		result.Checked = new(bool)
		*result.Checked = true
	}

	if menuItem.Click != nil {
		result.HasCallback = new(bool)
		*result.HasCallback = true
	}

	if menuItem.SubMenu != nil {
		result.SubMenu = m.NewProcessedMenu(menuItem.SubMenu)
	}

	// Add menu item to item map
	m.menuItemMap[ID] = menuItem

	// Add processed Item to processedMenuItems
	m.processedMenuItems[menuItem] = result

	return result
}

func (m *Manager) NewProcessedMenu(menu *menu.Menu) []*ProcessedMenuItem {

	if menu == nil {
		return nil
	}

	if menu.Items == nil {
		return nil
	}

	var result []*ProcessedMenuItem

	for _, item := range menu.Items {
		processedMenuItem := m.NewProcessedMenuItem(item)
		result = append(result, processedMenuItem)
	}

	return result
}

// WailsMenu is the original menu with the addition
// of radio groups extracted from the menu data
type WailsMenu struct {
	Menu              []*ProcessedMenuItem `json:",omitempty"`
	RadioGroups       []*RadioGroup        `json:",omitempty"`
	currentRadioGroup []string
}

// RadioGroup holds all the members of the same radio group
type RadioGroup struct {
	Members []string
	Length  int
}

func (m *Manager) NewWailsMenu(menu *menu.Menu) *WailsMenu {

	result := &WailsMenu{}

	// Process the menus
	result.Menu = m.NewProcessedMenu(menu)

	// Process the radio groups
	result.processRadioGroups()

	return result
}

func (w *WailsMenu) AsJSON() (string, error) {

	menuAsJSON, err := json.Marshal(w)
	if err != nil {
		return "", err
	}
	return string(menuAsJSON), nil
}

func (w *WailsMenu) processMenuItemForRadioGroups(item *ProcessedMenuItem) {

	switch item.Type {

	// We need to recurse submenus
	case menu.SubmenuType:

		// Finalise any current radio groups as they don't trickle down to submenus
		w.finaliseRadioGroup()

		// Process each submenu item
		for _, subitem := range item.SubMenu {
			w.processMenuItemForRadioGroups(subitem)
		}
	case menu.RadioType:
		// Add the item to the radio group
		w.currentRadioGroup = append(w.currentRadioGroup, item.ID)
	default:
		w.finaliseRadioGroup()
	}
}

func (w *WailsMenu) processRadioGroups() {

	if w.Menu == nil {
		return
	}
	// Loop over top level menus
	for _, item := range w.Menu {
		// Process MenuItem
		w.processMenuItemForRadioGroups(item)
	}

	w.finaliseRadioGroup()
}

func (w *WailsMenu) finaliseRadioGroup() {

	// If we were processing a radio group, fix up the references
	if len(w.currentRadioGroup) > 0 {

		// Create new radiogroup
		group := &RadioGroup{
			Members: w.currentRadioGroup,
			Length:  len(w.currentRadioGroup),
		}
		w.RadioGroups = append(w.RadioGroups, group)

		// Empty the radio group
		w.currentRadioGroup = []string{}
	}
}
