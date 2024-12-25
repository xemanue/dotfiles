return
{
    "nvim-treesitter/nvim-treesitter",
    build = ":TSUpdate",
    opts = {
        ensure_installed = {
            "c",
            "cpp",
            "lua",
            "vim",
            "vimdoc",
            "python",
            "html",
            "css",
            "json",
            "yaml",
            "ini",
            "markdown",
            "markdown_inline",
            "rust",
            "javascript",
            "sql",
        },
        sync_install = false,
        highlight = { enable = true, },
        indent = { enable = true, },
    }
}
