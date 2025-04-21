return {
    {
        "nvim-telescope/telescope.nvim",
        version = false,
        dependencies = {
            "nvim-lua/plenary.nvim"
        },
        keys = {
            { "<leader>f", "<cmd>Telescope find_files<cr>" },
            { "<leader>/", "<cmd>Telescope live_grep<cr>" },
            { "<leader>r", "<cmd>Telescope oldfiles<cr>" },
            { "<leader>m", "<cmd>Telescope marks<cr>" },
        },
        opts = function ()
            local actions = require("telescope.actions")
            local layout = require("telescope.actions.layout")
            
            require("telescope").setup {
                defaults = {
                    borderchars = { '─', '│', '─', '│', '┌', '┐', '┘', '└' },
                    layout_strategy = "horizontal",
                    layout_config = {
                        bottom_pane = {
                            height = 2,
                            prompt_position = "top"
                        },
                        horizontal = {
                            height = 0.7,
                            prompt_position = "top",
                            width = 0.7,
                            preview_width = 0.5
                        },
                    },
                    mappings = {
                        i = {
                            ["<esc>"] = actions.close,
                            ["<C-p>"] = layout.toggle_preview,
                            ["<C-b>"] = actions.select_horizontal,
                        },
                    },
                    path_display = {
                        "filename_first",
                        shorten = {
                            len = 2,
                            exclude = { -1, -2 },
                        },
                    },
                    sorting_strategy = "ascending",
                },
                pickers = {
                    find_files = {
                        hidden = true,
                    }
                }
            }
        end
    },
}
