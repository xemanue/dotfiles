return {
    {
        "neovim/nvim-lspconfig",
        config = function()
            require("cmp").setup {
                sources = {
                    { name = "nvim_lsp" },
                }
            }

            local capabilities = require("cmp_nvim_lsp").default_capabilities()
            local lspconfig = require("lspconfig")

            lspconfig.lua_ls.setup {
                capabilities = capabilities,
                settings = {
                    Lua = {
                        workspace = {
                            checkThirdParty = false,
                            library = { vim.env.VIMRUNTIME },
                        },
                        telemetry = {
                            enable = false,
                        },
                    },
                }
            }
            lspconfig.pylsp.setup {
                capabilities = capabilities,
            }
        end
    },
    {
        "L3MON4D3/LuaSnip",
        dependencies = {
            "saadparwaiz1/cmp_luasnip",
            "rafamadriz/friendly-snippets",
        },
    },
    {
        "hrsh7th/nvim-cmp",
        lazy = false,
        config = function()
            local cmp = require("cmp")
            local lspkind = require("lspkind")

            cmp.setup {
                formatting = {
                    fields = { "kind", "abbr" },
                    format = lspkind.cmp_format({
                        mode = "symbol",
                        maxwidth = {
                            menu = 50,
                            abbr = 50,
                        },
                    })
                },
                snippet = {
                    expand = function(args)
                        require('luasnip').lsp_expand(args.body)
                    end,
                },
                sources = {
                    { name = "nvim_lsp" },
                    { name = "luasnip" },
                },
                mapping = cmp.mapping.preset.insert ({
                    ['<C-j>'] = cmp.mapping(function(fallback)
                        if cmp.visible() then
                            cmp.select_next_item()
                        else
                            fallback()
                        end
                    end, { "i", "s" }),
                    ['<C-k>'] = cmp.mapping(function(fallback)
                        if cmp.visible() then
                            cmp.select_prev_item()
                        else
                            fallback()
                        end
                    end, { "i", "s", "c" }),
                    ['<C-Space>'] = cmp.mapping(function(fallback)
                        if cmp.visible() then
                            vim.cmd("let &undolevels = &undolevels")
                            cmp.confirm({ select = true })
                        else
                            fallback()
                        end
                    end, { "i", "s", "c" }),
                    ['<Esc>'] = cmp.mapping(function(fallback)
                        if cmp.visible() then
                            cmp.abort()
                        else
                            vim.api.nvim_feedkeys(vim.api.nvim_replace_termcodes("<C-c>", true, true, true), "n", true)
                        end
                    end, { "i", "s", "c" }),
                })
            }

            vim.keymap.set("i", "<C-u>", "<cmd>undo<cr>")
        end,
    },
    {
        "hrsh7th/cmp-nvim-lsp",
        lazy = false,
    },
    {
        "onsails/lspkind.nvim"
    }
}
