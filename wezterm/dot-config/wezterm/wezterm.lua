-- Pull in the wezterm API
local wezterm = require 'wezterm'

-- This will hold the configuration.
local config = wezterm.config_builder()

local act = wezterm.action

config.font = wezterm.font_with_fallback ({
    { family = "Iosevkust" },
    { family = "Symbols Nerd Font Mono", scale = 0.75 }
})
config.font_size = 13
config.allow_square_glyphs_to_overflow_width = "Never"

config.adjust_window_size_when_changing_font_size = false
config.animation_fps = 30
config.audible_bell = "Disabled"

-- cell_widths might be good for nerd font
config.color_scheme = "Catppuccin Mocha"
config.cursor_blink_rate = 500
config.default_cursor_style = "BlinkingBlock"

-- Tab bar
config.enable_tab_bar = true
config.use_fancy_tab_bar = false
config.hide_tab_bar_if_only_one_tab = false
config.tab_bar_at_bottom = true
config.show_new_tab_button_in_tab_bar = false

config.leader = { key = 'a', mods = 'ALT', timeout_milliseconds = 1000 }

config.keys = {
    {
        key = 'a',
        mods = 'LEADER',
        action = act.AttachDomain 'unix',
    },
    {
        key = 'b',
        mods = 'LEADER',
        action = act.SplitVertical { domain = 'CurrentPaneDomain' },
    },
    {
        key = 'v',
        mods = 'LEADER',
        action = act.SplitHorizontal { domain = 'CurrentPaneDomain' },
    },
    {
        key = 'c',
        mods = 'LEADER',
        action = act.CloseCurrentPane { confirm = false },
    },
    {
        key = 's',
        mods = 'LEADER',
        action = act.PaneSelect,
    },
    {
        key = 'h',
        mods = 'LEADER',
        action = act.ActivatePaneDirection 'Left',
    },
    {
        key = 'j',
        mods = 'LEADER',
        action = act.ActivatePaneDirection 'Down',
    },
    {
        key = 'k',
        mods = 'LEADER',
        action = act.ActivatePaneDirection 'Up',
    },
    {
        key = 'l',
        mods = 'LEADER',
        action = act.ActivatePaneDirection 'Right',
    },
    {
        key = 't',
        mods = 'LEADER',
        action = act.SpawnTab 'CurrentPaneDomain',
    },
    {
        key = 'w',
        mods = 'LEADER',
        action = act.CloseCurrentTab { confirm = false },
    },
    {
        key = 'd',
        mods = 'LEADER',
        action = act.ShowTabNavigator,
    },
    {
        key = 'r',
        mods = 'LEADER',
        action = act.PromptInputLine {
            description = 'Enter a new name for the tab',
            action = wezterm.action_callback(function(window, pane, line)
                if line then
                    window:active_tab():set_title(line)
                end
            end),
        },
    },
}

for i = 1, 9 do
    table.insert(config.keys, {
        key = tostring(i),
        mods = 'LEADER',
        action = act.ActivateTab(i - 1),
    })
end

function tab_title(tab_info)
    local title = tab_info.tab_title
    local index = tab_info.tab_index + 1

    if title and #title > 0 then
        return index .. ': ' .. title
    end

    return index
end

wezterm.on(
    'format-tab-title',
    function(tab, tabs, panes, config, hover, max_width)
        local title = tab_title(tab)

        local background = '#181825'
        local foreground = '#a6adc8'

        if tab.is_active then
            background = '#b4befe'
            foreground = '#11111b'
        elseif hover then
            background = '#313244'
            foreground = '#cdd6f4'
        end

        title = wezterm.truncate_right(title, max_width - 2)

        return {
            { Background = { Color = background } },
            { Foreground = { Color = foreground } },
            { Text = " " .. title .. " " },
        }
    end
)




-- Finally, return the configuration to wezterm:
return config
