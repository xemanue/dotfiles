return
{
    "ellisonleao/gruvbox.nvim",
    name = "gruvbox",
    enabled = false,
    priority = 1000,
    config = function()
        local opts = require("gruvbox")
        opts.setup({
            terminal_colors = true, -- add neovim terminal colors
            undercurl = true,
            underline = true,
            bold = false,
            italic = {
                strings = false,
                emphasis = false,
                comments = false,
                operators = false,
                folds = false,
            },
            strikethrough = true,
            invert_selection = false,
            invert_signs = false,
            invert_tabline = false,
            invert_intend_guides = false,
            inverse = true, -- invert background for search, diffs, statuslines and errors
            contrast = "soft", -- can be "hard", "soft" or empty string
            dim_inactive = false,
            transparent_mode = false,
        })
        vim.o.background = "light"
        vim.cmd.colorscheme "gruvbox"
    end
}
