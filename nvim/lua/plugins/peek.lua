return
{
    "toppair/peek.nvim",
    event = { "VeryLazy" },
    build = "deno task --quiet build:fast",
    config = function()
        require("peek").setup({
            auto_load = false,
            syntax = true,
            theme = 'dark',
            update_on_change = true,
            app = 'browser'
        })
        vim.api.nvim_create_user_command("PeekOpen", require("peek").open, {})
        vim.api.nvim_create_user_command("PeekClose", require("peek").close, {})
        vim.keymap.set("n", "<leader>p", ":PeekOpen<CR>", {})
        vim.keymap.set("n", "<leader>o", ":PeekClose<CR>", {})
    end
}
