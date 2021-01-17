package menumanager

import (
	"github.com/matryer/is"
	"github.com/wailsapp/wails/v2/pkg/menu"
	"testing"
)

func TestManager_AddTrayMenu(t *testing.T) {

	is := is.New(t)

	simpleLabel := menu.Text("test", nil, nil)
	checkbox := menu.Checkbox("test", true, nil, nil)
	radioGroup1 := menu.Radio("option 1", true, nil, nil)
	radioGroup2 := menu.Radio("option 2", false, nil, nil)
	radioGroup3 := menu.Radio("option 3", false, nil, nil)
	callback := menu.Text("Preferences", nil, func(_ *menu.CallbackData) {})

	empty := &menu.TrayMenu{}
	labelOnly := &menu.TrayMenu{Label: "test"}
	iconOnly := &menu.TrayMenu{Icon: "svelte"}
	iconLabel := &menu.TrayMenu{Icon: "svelte", Label: "test"}
	blankLabel := &menu.TrayMenu{Label: ""}
	blankMenu := &menu.TrayMenu{Menu: menu.NewMenu()}
	menuTextItem := &menu.TrayMenu{Menu: menu.NewMenuFromItems(simpleLabel)}
	checkboxItem := &menu.TrayMenu{Menu: menu.NewMenuFromItems(checkbox)}
	radioGroupItems := &menu.TrayMenu{Menu: menu.NewMenuFromItems(radioGroup1, radioGroup2, radioGroup3)}
	callbackItem := &menu.TrayMenu{Menu: menu.NewMenuFromItems(callback)}

	tests := []struct {
		trayMenu *menu.TrayMenu
		want     string
	}{
		{empty, "{\"I\":\"T1\"}"},
		{labelOnly, "{\"I\":\"T1\",\"l\":\"test\"}"},
		{iconOnly, "{\"I\":\"T1\",\"i\":\"svelte\"}"},
		{iconLabel, "{\"I\":\"T1\",\"l\":\"test\",\"i\":\"svelte\"}"},
		{blankLabel, "{\"I\":\"T1\"}"},
		{blankMenu, "{\"I\":\"T1\"}"},
		{menuTextItem, "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"t\"}]}"},
		{checkboxItem, "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"c\",\"c\":true}]}"},
		{radioGroupItems, "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"option 1\",\"t\":\"r\",\"c\":true},{\"I\":\"2\",\"l\":\"option 2\",\"t\":\"r\"},{\"I\":\"3\",\"l\":\"option 3\",\"t\":\"r\"}],\"r\":[{\"Members\":[\"1\",\"2\",\"3\"],\"Length\":3}]}"},
		{callbackItem, "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"Preferences\",\"t\":\"t\",\"C\":true}]}"},
	}
	for _, tt := range tests {
		m := NewManager()
		got := m.AddTrayMenu(tt.trayMenu)
		JSON, err := got.AsJSON()
		is.NoErr(err)
		is.Equal(JSON, tt.want)
	}

}

func TestManager_CallbackMap(t *testing.T) {

	is := is.New(t)

	simpleLabel := menu.Text("test", nil, nil)
	simpleLabelWithCallback := menu.Text("test", nil, func(_ *menu.CallbackData) {})
	checkboxWithCallback := menu.Checkbox("test", true, nil, func(_ *menu.CallbackData) {})

	blankMenu := &menu.TrayMenu{Menu: menu.NewMenu()}
	noCallback := &menu.TrayMenu{Menu: menu.NewMenuFromItems(simpleLabel)}
	oneMenuWithCallback := &menu.TrayMenu{Menu: menu.NewMenuFromItems(simpleLabelWithCallback)}
	duplicateCallbacks := &menu.TrayMenu{Menu: menu.NewMenuFromItems(simpleLabelWithCallback, simpleLabelWithCallback)}
	twoMenusWithCallbacks := &menu.TrayMenu{Menu: menu.NewMenuFromItems(simpleLabelWithCallback, checkboxWithCallback)}
	duplicateMenusWithCallbacks := &menu.TrayMenu{Menu: menu.NewMenuFromItems(simpleLabelWithCallback, checkboxWithCallback, simpleLabelWithCallback, checkboxWithCallback)}

	tests := []struct {
		trayMenu  *menu.TrayMenu
		trays     int
		menuItems int
		JSON      string
	}{
		{blankMenu, 1, 0, "{\"I\":\"T1\"}"},
		{noCallback, 1, 1, "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"t\"}]}"},
		{oneMenuWithCallback, 1, 1, "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"t\",\"C\":true}]}"},
		{duplicateCallbacks, 1, 1, "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"t\",\"C\":true},{\"I\":\"1\"}]}"},
		{twoMenusWithCallbacks, 1, 2, "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"t\",\"C\":true},{\"I\":\"2\",\"l\":\"test\",\"t\":\"c\",\"c\":true,\"C\":true}]}"},
		{duplicateMenusWithCallbacks, 1, 2, "{\"I\":\"T1\",\"m\":[{\"I\":\"1\",\"l\":\"test\",\"t\":\"t\",\"C\":true},{\"I\":\"2\",\"l\":\"test\",\"t\":\"c\",\"c\":true,\"C\":true},{\"I\":\"1\"},{\"I\":\"2\"}]}"},
	}
	for _, test := range tests {
		m := NewManager()
		tm := m.AddTrayMenu(test.trayMenu)
		is.Equal(len(m.trayMenuMap), test.trays)
		is.Equal(len(m.menuItemMap), test.menuItems)
		JSON, err := tm.AsJSON()
		is.NoErr(err)
		is.Equal(JSON, test.JSON)
	}

}
