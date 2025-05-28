return {
    'nvim-telescope/telescope.nvim',
    tag = '0.1.8',
    dependencies = { "nvim-lua/plenary.nvim" },
    keys = { },
    config = function()
        local actions = require("telescope.actions")
        local layout = require("telescope.actions.layout")

        require("telescope").setup {
            defaults = {
                borderchars = { '─', '│', '─', '│', '┌', '┐', '┘', '└' },
                hidden = true,
                layout_config = {

                },
                mappings = {
                    i = {
                        ["<C-p>"] = layout.toggle_preview,
                        ["<C-b>"] = actions.select_horizontal,
                        ["<C-v>"] = actions.select_vertical
                    },
                    n = {
                        ["<esc>"] = actions.close,
                    },
                },
                prompt_prefix = "> ",
            },
        }
    end
}
