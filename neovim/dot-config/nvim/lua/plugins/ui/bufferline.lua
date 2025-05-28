return {
    'akinsho/bufferline.nvim',
    event = "VeryLazy",
    dependencies = "nvim-tree/nvim-web-devicons",
    opts = {
        options = {
            right_mouse_command = nil,
            middle_mouse_command = function(n) Snacks.bufdelete(n) end,

        },      
    },
}
