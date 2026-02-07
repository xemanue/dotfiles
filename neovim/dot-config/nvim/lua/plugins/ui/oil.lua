return {
    'stevearc/oil.nvim',
    ---@module 'oil'
    ---@type oil.SetupOpts
    dependencies = { "nvim-tree/nvim-web-devicons" },
    lazy = false,
    keys = {
        { "-", "<cmd>Oil --float<cr>", desc = "Open file explorer"},
    },
    config = function()
        require("oil").setup({
            view_options = {
                show_hidden = true,
            },
            float = {
                border = "single",
                max_width = 0.7,
                max_height = 0.6,
            },
            confirmation = {
                border = "single",
            },
            progress = {
                border = "single",
            },
            ssh = {
                border = "single",
            },
            keymaps_help = {
                border = "single",
            },
            keymaps = {
                ["<esc>"] = { "actions.close", mode = "n" },
                [";"] = { "actions.select", mode = "n" },
                ["<C-v>"] = { "actions.select", mode = "n", opts = { vertical = true } },
                ["<C-b>"] = { "actions.select", mode = "n", opts = { horizontal = true } },
            }
        })

        vim.api.nvim_set_hl(0, "NormalFloat", { fg = "#cdd6f4", bg = "#1e1e2e"})
        vim.api.nvim_set_hl(0, "FloatBorder", { fg = "#89b4fa", bg = "#1e1e2e"})
        vim.api.nvim_set_hl(0, "FloatTitle", { fg = "#1e1e2e", bg = "#89b4fa"})
    end
}
