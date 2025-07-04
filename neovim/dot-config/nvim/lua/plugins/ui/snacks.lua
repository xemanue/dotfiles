local close_explorer = function()
    local explorer = require("mini.files")
    if not explorer.open() then explorer.close() end
end

return {
    "folke/snacks.nvim",
    priority = 1000,
    lazy = false,
    opts = {
        bufdelete = { enabled = true },
        indent = { enabled = true },
        lazygit = { enabled = true },
        notifier = { enabled = false},
        picker = { -- Background: SnacksNormal / SnacksPicker
            enabled = true,
            prompt = "> ",
            layouts = {
                default = {
                    layout = {
                        backdrop = false,
                        width = 0.5,
                        min_width = 80,
                        height = 0.8,
                        min_height = 30,
                        box = "vertical",
                        border = "single", -- Uses FloatBorder highlight
                        title = "{title} {live} {flags}",
                        title_pos = "center",
                        { win = "input", height = 1, border = "bottom" },
                        { win = "list", border = "none" },
                        { win = "preview", title = "{preview}", height = 0.4, border = "top" },
                    },

                }
            },
        },
        scroll = { enabled = true },
    },
    keys = {
        { "M", function() require("snacks").bufdelete() end, desc = "Close current buffer" },

        { "<leader>gl", function() require("snacks").lazygit() end, desc = "Open Lazygit" },

        { "<leader>ff", function() close_explorer() require("snacks").picker.files(opts) end },
        { "<leader>fg", function() close_explorer() require("snacks").picker.grep(opts) end },
        { "<leader>fr", function() close_explorer() require("snacks").picker.recent(opts) end },
        { "<leader>fm", function() close_explorer() require("snacks").picker.marks(opts) end },
        { "<leader>fh", function() close_explorer() require("snacks").picker.highlights(opts) end },
        { "<leader>fc", function() close_explorer() require("snacks").picker.command_history(opts) end },
    },
}
