local wezterm = require("wezterm")
local config = wezterm.config_builder()
local act = wezterm.action

config = {

  --=========================================================================--
  -- Appearance
  
  -- Theme
  colors = {
    foreground = "#d0d0d8",
    background = "#08080c",

    ansi = {
      "#d0d0d8", "#d0d0d8", "#d0d0d8", "#d0d0d8",
      "#d0d0d8", "#d0d0d8", "#d0d0d8", "#d0d0d8",
    },

    brights = {
      "#f0f0ff", "#f0f0ff", "#f0f0ff", "#f0f0ff",
      "#f0f0ff", "#f0f0ff", "#f0f0ff", "#f0f0ff",
    },

    cursor_fg = "#08080c",
    cursor_bg = "#ff8080",
    cursor_border = "#ff8080",
    compose_cursor = "#df8088",
    selection_bg = "#1a1a22",

    tab_bar = {
      background = "#0d0d11",
      
      active_tab = {
        bg_color = "#0d0d11", fg_color = "#ff8080",
        italic = false,
      },

      inactive_tab = {
        bg_color = "#0d0d11", fg_color = "#383840",
      },
      
      inactive_tab_hover = {
        bg_color = "#303030", fg_color = "#878787",
      },
    },
  },


  -- Font

  font = wezterm.font_with_fallback({
    { family = "Iosevkust NFM", weight = "Regular" },
  }),

  font_size = 13,
  allow_square_glyphs_to_overflow_width = "Never",

  default_cursor_style = "SteadyBlock",
  cursor_blink_rate = 500,


  -- Tabs

  enable_tab_bar = true,
  use_fancy_tab_bar = false,
  hide_tab_bar_if_only_one_tab = false,
  tab_bar_at_bottom = true,
  show_new_tab_button_in_tab_bar = false,


  -- Misc
  
  animation_fps = 30,
  audible_bell = "Disabled",
  adjust_window_size_when_changing_font_size = false,


  --=========================================================================--
  -- Binds

  leader = { key = ' ', mods = 'SHIFT', timeout_milliseconds = 2000 },

  keys = {
    {
      key = 't', mods = 'LEADER', action = act.SpawnTab 'CurrentPaneDomain'
    },
    {
      key = "h", mods = "LEADER", action = act.ActivateTabRelative(-1)
    },
    {
      key = "l", mods = "LEADER", action = act.ActivateTabRelative(1)
    },
    {
      key = "w", mods = "LEADER", action = act.CloseCurrentTab({ confirm = true })
    },
    {
      key = 'b', mods = 'LEADER', action = act.SplitVertical {
        domain = 'CurrentPaneDomain'
      }
    },
    {
      key = 'v', mods = 'LEADER', action = act.SplitHorizontal { 
        domain = 'CurrentPaneDomain'
      }
    },
    {
      key = 'h', mods = 'LEADER', action = act.ActivatePaneDirection 'Left'
    },
    {
      key = 'j', mods = 'LEADER', action = act.ActivatePaneDirection 'Down'
    },
    {
      key = 'k', mods = 'LEADER', action = act.ActivatePaneDirection 'Up'
    },
    {
      key = 'l', mods = 'LEADER', action = act.ActivatePaneDirection 'Right'
    },
    {
      key = 'c', mods = 'LEADER', action = act.CloseCurrentPane {
        confirm = true
      }
    },
    {
      key = 'r', mods = 'LEADER', action = act.PromptInputLine {
        description = 'Enter a new name for the tab',
        action = wezterm.action_callback(function(window, _, line)
          if line then
            window:active_tab():set_title(line)
          end
        end),
      },
    },
  }
}

--===========================================================================--
-- Snippets

-- BIND: Tab navigation

for i = 1, 9 do
  table.insert(config.keys, {
    key = tostring(i),
    mods = 'LEADER',
    action = act.ActivateTab(i - 1),
  })
end


-- THEME: Tab titles

function Tab_title(tab_info)
  local title = tab_info.tab_title
  local index = tab_info.tab_index + 1

  if title and #title > 0 then
    return index .. ' | ' .. title
  end

  return index
end


-- THEME: Tab appearance

wezterm.on( 'format-tab-title',
  function(tab, _, _, _, hover, max_width)
    local title = Tab_title(tab)

    if tab.is_active then
      background = config.colors.tab_bar.active_tab.bg_color
      foreground = config.colors.tab_bar.active_tab.fg_color
    elseif hover then
      background = config.colors.tab_bar.inactive_tab_hover.bg_color
      foreground = config.colors.tab_bar.inactive_tab_hover.fg_color
    else
      background = config.colors.tab_bar.inactive_tab.bg_color
      foreground = config.colors.tab_bar.inactive_tab.fg_color
    end

    title = wezterm.truncate_right(title, max_width - 2)

    return {
      { Attribute = { Italic = false } },
      { Background = { Color = background } },
      { Foreground = { Color = foreground } },
      { Text = " " .. title .. " " },
    }
  end
)

return config
