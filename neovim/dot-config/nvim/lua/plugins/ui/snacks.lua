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
        scroll = { enabled = false },
    },
    keys = {
        { "C", function() Snacks.bufdelete() end, desc = "[C]lose current buffer" },
    },
}
