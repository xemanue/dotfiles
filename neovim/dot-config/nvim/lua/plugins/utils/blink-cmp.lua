return {
    'saghen/blink.cmp',
    dependencies = { 'rafamadriz/friendly-snippets' },
    version = '1.*',

    ---@module 'blink.cmp'
    ---@type blink.cmp.Config
    opts_extend = { "sources.default" },
    config = function()
        require("blink.cmp").setup({
            keymap = {
                preset = "none",

                ["<A-k>"] = { "select_prev", "fallback" },
                ["<A-j>"] = { "select_next", "fallback" },
                ["<A-l>"] = { "accept", "fallback" },
                ["<A-h>"] = { "show_documentation" },
            },

            appearance = {
                nerd_font_variant = 'normal'
            },

            completion = {
                documentation = { auto_show = false },
                list = {
                    selection = { auto_insert = false },
                },
            },

            sources = {
                default = { 'lsp', 'path', 'snippets', 'buffer' },
            },

            fuzzy = { implementation = "prefer_rust_with_warning" },
        })
        vim.api.nvim_set_hl(0, "BlinkCmpDoc", { fg = "#C6D0F6", bg = "#292C3C" })
        vim.api.nvim_set_hl(0, "BlinkCmpDocSeparator", { fg = "#C6D0F6", bg = "#292C3C" })
        vim.api.nvim_set_hl(0, "BlinkCmpDocBorder", { fg = "#C6D0F6", bg = "#292C3C" })
    end,
}
