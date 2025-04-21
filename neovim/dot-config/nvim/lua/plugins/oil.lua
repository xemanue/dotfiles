return {
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
}
