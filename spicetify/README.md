# Spicetify edited text theme
## Disclaimer
This is an edited version of [darkthemer](https://github.com/darkthemer)'s [text theme](https://github.com/darkthemer/spicetify-themes/tree/master/text) for [Spicetify](https://spicetify.app/), so all credits go to them.

Most changes are a matter of personal preference, but I also fixed some bugs I encountered while using Spotify `1.2.22.982`.

## Instalation
1. [Install Spicetify](https://spicetify.app/docs/advanced-usage/installation/).
2. Download `user.css` and `color.ini` and move them to `%appdata%/spicetify/Themes/text/`.
3. Change the theme by running `spicetify config current_theme text` in PowerShell.
4. (Optional) Choose your preferred color scheme (Spotify, Spicetify, CatppuccinMocha, CatppuccinMacchiato, CatppuccinFrappe, Dracula, Gruvbox, Kanagawa, Nord, Rigel, RosePine, RosePineMoon, Solarized, TokyoNight, TokyoNightStorm or ForestGreen) by running `spicetify config color_scheme <you_choose>`.
5. Add the following under `[Patch]` in `%appdata%/spicetify/config-xpui.ini`. Details as to why explained [here](https://github.com/JulienMaille/spicetify-dynamic-theme#important).
    xpui.js_find_8008 = ,(\w+=)56,
    xpui.js_repl_8008 = ,${1}32,
6. Run `spicetify apply` to apply changes.
