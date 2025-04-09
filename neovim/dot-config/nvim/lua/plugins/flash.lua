return {
    "folke/flash.nvim",
    event = "VeryLazy",
    -- @type Flash.Config
    opts = {
        modes = {
            char = {
                enabled = false,
            },
        },
    },
    -- stylua: ignore
    keys = {
        { "f", mode = { "n", "x", "o" }, function() require("flash").jump() end, desc = "Flash" },
        { "<c-f>", mode = { "c" }, function() require("flash").toggle() end, desc = "Toggle Flash Search" },
    },
}
