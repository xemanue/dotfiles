return {
    "folke/which-key.nvim",
    event = "VeryLazy",
    opts = {
        preset = "helix",
        plugins = {
            spelling = { enabled = false },
        },
        win = {
            border = "single",
        },
        icons = {
            separator = "-",
            mappings = false,
        },
    },
}
