-- Pull in the wezterm API
local wezterm = require 'wezterm'

-- This will hold the configuration.
local config = wezterm.config_builder()

-- This is where you actually apply your config choices.

config.font = wezterm.font 'Iosevkust'
config.font_size = 13

config.adjust_window_size_when_changing_font_size = false
config.animation_fps = 30
config.audible_bell = "Disabled"
-- cell_widths might be good for nerd font
config.cursor_blink_rate = 500
config.default_cursor_style = "BlinkingBlock"
config.enable_tab_bar = false

config.color_schemes = {
    ['test'] = {
        -- char_select_bg_color
        -- char_select_fg_color
        -- command_palette_bg_color
        -- command_palette_fg_color
    }
}

-- Finally, return the configuration to wezterm:
return config
