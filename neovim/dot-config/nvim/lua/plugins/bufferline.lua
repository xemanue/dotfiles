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
                        highlight = "Directory",
                        separator = true,
                    }
                },
                separator_style = "slant"
            }
        }
    end
}
