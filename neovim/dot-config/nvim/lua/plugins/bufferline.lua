return
{
    'akinsho/bufferline.nvim',
    version = "*",
    dependencies = 'nvim-tree/nvim-web-devicons',
    config = function()
        vim.opt.termguicolors = true

        local bufferline = require("bufferline")
        bufferline.setup {
            options = {
                style_preset = bufferline.style_preset.minimal,
                right_mouse_command = false,
                middle_mouse_command = "bdelete! %d",
                offsets = {
                    {
                        filetype = "neo-tree",
                        text = "Neotree",
                        highlight = "Directory",
                        text_align = "left",
                        separator = "|"
                    }
                },
                separator_style = "slant"
            }
        }
    end
}
