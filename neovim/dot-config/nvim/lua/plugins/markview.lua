return
{
    "OXY2DEV/markview.nvim",
    lazy = false,
    dependencies = {
        "nvim-treesitter/nvim-treesitter",
        "nvim-tree/nvim-web-devicons"
    },
    config = function()
        local presets = require("markview.presets");

        require ("markview").setup({
            checkboxes = presets.checkboxes.nerd,
            markdown = {
                horizontal_rules = presets.horizontal_rules.thick,

                headings = {
                    shift_width = 1,

                    heading_1 = {
                        style = "icon",
                        hl = "MarkviewHeading1",
                        icon = " ",
                        sign = "",
                    },
                    heading_2 = {
                        style = "icon",
                        hl = "MarkviewHeading2",
                        icon = " ",
                        sign = "",
                    },
                    heading_3 = {
                        style = "icon",
                        hl = "MarkviewHeading3", 
                        icon = " ",
                        sign = "",
                    },
                    heading_4 = {
                        style = "icon",
                        hl = "MarkviewHeading4", 
                        icon = " ",
                        sign = "",
                    },
                    heading_5 = {
                        style = "icon",
                        hl = "MarkviewHeading5", 
                        icon = " ",
                        sign = "",
                    },
                    heading_6 = {
                        style = "icon",
                        hl = "MarkviewHeading6", 
                        icon = " ",
                        sign = "",
                    },
                }
            },
        });
    end
}
