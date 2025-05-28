return {
    {
        "catppuccin/nvim",
        name = "catppuccin",
        priority = 1000,
        config = function()
            require("catppuccin").setup({
                flavour = "frappe",
                no_italic = true,
                no_bold = true,
                no_underline = true,
            })

            vim.cmd("colorscheme catppuccin")

            -- Custom highlight groups
            vim.api.nvim_set_hl(0, "NormalFloat", { fg = "#C6D0F6", bg = "#303447"})
        end,
    },
}
