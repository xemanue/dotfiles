return
{
    {
        "williamboman/mason.nvim",
        enabled = false,
        config = function()
            require("mason").setup()
        end
    },
    {
        "williamboman/mason-lspconfig.nvim",
        enabled = false,
        config = function()
            require("mason-lspconfig").setup({
                ensure_installed = {
                    "lua_ls",
                    "clangd",
                    "cssls",
                    "html",
                    "ts_ls",
                    "jsonls",
                    "marksman",
                    "pylsp",
                    "rust_analyzer",
                    "sqlls",
                    "vimls",
                }
            })
        end
    },
    {
        "neovim/nvim-lspconfig",
        enabled = false,
        config = function()
            local lspconfig = require("lspconfig")
            lspconfig.lua_ls.setup({})
            lspconfig.clangd.setup({})
            lspconfig.cssls.setup({})
            lspconfig.html.setup({})
            lspconfig.ts_ls.setup({})
            lspconfig.jsonls.setup({})
            lspconfig.marksman.setup({})
            lspconfig.pylsp.setup({})
            lspconfig.rust_analyzer.setup({})
            lspconfig.sqlls.setup({})
            lspconfig.vimls.setup({})

            vim.keymap.set('n', 'gD', vim.lsp.buf.declaration, opts)
            vim.keymap.set('n', 'gd', vim.lsp.buf.definition, opts)
            vim.keymap.set('n', 'K', vim.lsp.buf.hover, opts)
            vim.keymap.set('n', 'gi', vim.lsp.buf.implementation, opts)
            vim.keymap.set({ 'n', 'v' },  '<leader>ca', vim.lsp.buf.code_action, opts)
            vim.keymap.set('n',  '<leader>rn', vim.lsp.buf.rename, opts)
            vim.keymap.set('n',  '<leader>gr', vim.lsp.buf.references, opts)
        end
    }
}
