package menu

// Type of the menu item
type Type string

const (
	// TextType is the text menuitem type
	TextType Type = "t"
	// SeparatorType is the Separator menuitem type
	SeparatorType Type = "s"
	// SubmenuType is the Submenu menuitem type
	SubmenuType Type = "S"
	// CheckboxType is the Checkbox menuitem type
	CheckboxType Type = "c"
	// RadioType is the Radio menuitem type
	RadioType Type = "r"
)
