return
{
    "iamcco/markdown-preview.nvim",

    cmd = { "MarkdownPreviewToggle", "MarkdownPreview", "MarkdownPreviewStop" },
    build = "cd app && yarn install",
    init = function()
        vim.g.mkdp_filetypes = { "markdown" }
        vim.g.mkdp_browser = 'firefox'
    end,
    config = function ()
        vim.keymap.set("n", "<leader>p", ":MarkdownPreviewToggle<CR>", {})
    end,
    ft = { "markdown" },
}
