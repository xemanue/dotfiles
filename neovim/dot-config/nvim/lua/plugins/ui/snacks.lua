return {
    "folke/snacks.nvim",
    priority = 1000,
    lazy = false,
    keys = {
        { "M", function() require("snacks").bufdelete() end, desc = "Close current buffer" },

        { "<leader>gl", function() require("snacks").lazygit() end, desc = "Open Lazygit" },

        { "<leader>ff", function() require("snacks").picker.files() end },
        { "<leader>fg", function() require("snacks").picker.grep() end },
        { "<leader>fr", function() require("snacks").picker.recent() end },
        { "<leader>fm", function() require("snacks").picker.marks() end },
        { "<leader>fc", function() require("snacks").picker.highlights() end },
        { "<leader>fh", function() require("snacks").picker.command_history() end },
    },
    config = function()
        opts = {
            bufdelete = { enabled = true },
            indent = { enabled = true },
            lazygit = { enabled = true },
            notifier = { enabled = true },
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
        }

        require("snacks").setup(opts)
    end
}
