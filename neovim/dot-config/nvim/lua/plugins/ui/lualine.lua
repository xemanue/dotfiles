return {
    "nvim-lualine/lualine.nvim",
    dependencies = { "nvim-tree/nvim-web-devicons" },
    config = function()
        local inactive = function()
            return "INACTIVE"
        end
        opts = {
            options = {
                theme = "catppuccin",
                component_separators = "|",
                section_separators = "",
            },
            sections = {
                lualine_a = { "mode" },
                lualine_b = { "branch", "diff", "diagnostics" },
                lualine_c = { "filename" },
                lualine_x = { "filetype" },
                lualine_y = { "progress" },
                lualine_z = { "location" }
            },
            inactive_sections = {
                lualine_a = {
                    {
                        "mode",
                        color = { bg = "#737995", fg = "#292C3D"},
                    }
                },
                lualine_b = { "branch", "diff", "diagnostics" },
                lualine_c = { "filename" },
                lualine_x = { "filetype" },
                lualine_y = {
                    {
                        "progress",
                        color = "lualine_c_inactive",
                    }
                },
                lualine_z = {
                    {
                        "location",
                        color = { bg = "#737995", fg = "#292C3D"},
                    }
                }
            },
        }

        require("lualine").setup(opts)
    end
}
