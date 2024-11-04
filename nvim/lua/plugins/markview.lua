return
{
    "OXY2DEV/markview.nvim",
    lazy = false,
    dependencies = {
        "nvim-treesitter/nvim-treesitter",
        "nvim-tree/nvim-web-devicons"
    },
    config = function()
        vim.keymap.set("n", "<leader>o", ":Markview<CR>", {})
    end
}
