return {
    'akinsho/bufferline.nvim',
    event = "VeryLazy",
    dependencies = "nvim-tree/nvim-web-devicons",
    config = function()
        local bufferline = require("bufferline")
        bufferline.setup({
            options = {
                right_mouse_command = nil,
                middle_mouse_command = function(n) Snacks.bufdelete(n) end,

                style_preset = {
                    bufferline.style_preset.minimal,
                    bufferline.style_preset.no_italic,
                    bufferline.style_preset.no_bold,
                },
            }
        })
    end
}
