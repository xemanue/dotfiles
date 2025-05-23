return {
    {
        "norcalli/nvim-colorizer.lua"
    },
    {
        "nvim-lualine/lualine.nvim",
        dependencies = { 'nvim-tree/nvim-web-devicons' },
        config = function()
            require('lualine').setup({
                options = {
                    icons_enabled = true,
                    theme = "auto", -- or 'dracula', 'tokyonight', or your preferred theme
                    section_separators = "",
                    component_separators = { left = "|", right = "|" },
                    globalstatus = true,
                },
                sections = {
                    lualine_a = { { "mode", upper = true } },
                    lualine_b = { "branch", "diff" },
                    lualine_c = { { "filename", file_status = true, path = 0 }, } ,
                    lualine_x = {
                        "encoding",
                        "filetype",
                    },
                    lualine_y = { "progress" },
                    lualine_z = { "location" },
                },
                inactive_sections = {
                    lualine_a = {},
                    lualine_b = {},
                    lualine_c = { { "filename", file_status = true, path = 1 } },
                    lualine_x = { "location" },
                    lualine_y = {},
                    lualine_z = {},
                },
                tabline = {},
                extensions = { "lazy", "man", "oil" }
            })

            vim.opt.showmode = false
        end
    },
    {
        'stevearc/oil.nvim',
        ---@module 'oil'
        ---@type oil.SetupOpts
        opts = {
            view_options = {
                show_hidden = true,
            },
            float = {
                border = "single",
                max_width = 0.7,
                max_height = 0.7,
            },
            confirmation = {
                border = "single",
            },
            keymaps = {
                ["<esc>"] = "actions.close",
                ["<C-v>"] = { "actions.select", opts = { vertical = true } },
                ["<C-b>"] = { "actions.select", opts = { horizontal = true } },
            },
        },
        dependencies = { "nvim-tree/nvim-web-devicons" },
        lazy = false,
        keys = {
            { "<leader>-", "<cmd>Oil --float<cr>" },
        }
    },
    {
        "folke/snacks.nvim",
        opts = {
            dashboard = {
                enabled = true,
                preset = {
                    header = [[
▗▖  ▗▖▗▞▀▚▖ ▄▄▄  ▄   ▄ ▄ ▄▄▄▄ 
▐▛▚▖▐▌▐▛▀▀▘█   █ █   █ ▄ █ █ █
▐▌ ▝▜▌▝▚▄▄▖▀▄▄▄▀  ▀▄▀  █ █   █
▐▌  ▐▌                 █      ]],
                    keys = {
                        { icon = "󰈈 ", key = "-", desc = "View Files", action = ":Oil --float" },
                        { icon = " ", key = "n", desc = "New File", action = ":ene | startinsert" },
                        { icon = " ", key = "f", desc = "Find File", action = ":lua Snacks.dashboard.pick('files')" },
                        { icon = " ", key = "/", desc = "Find Text", action = ":lua Snacks.dashboard.pick('live_grep')" },
                        { icon = " ", key = "r", desc = "Recent Files", action = ":lua Snacks.dashboard.pick('oldfiles')" },
                        { icon = " ", key = "r", desc = "Restore Session", section = "session" },
                        { icon = "󰒲 ", key = "l", desc = "Lazy", action = ":Lazy", enabled = package.loaded.lazy ~= nil },
                        { icon = " ", key = "q", desc = "Quit", action = ":qa" }
                    },
                },
                sections = {
                    {
                        { section = "header" },
                        { section = "keys", padding = 1 },
                        { section = "startup" },
                    },
                }
            },
            picker = {
                layout = {
                    width = 0.5,
                    height = 0.5,
                    {
                        border = "single",
                    },
                },
            },
        }
    },
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
