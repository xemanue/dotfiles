return
{
    {
        "L3MON4D3/LuaSnip",
        version = "v2.*",
        build = "make install_jsregexp",
        dependencies = {
            "saadparwaiz1/cmp_luasnip",
            "rafamadriz/friendly-snippets",
        }
    },
    {
        "hrsh7th/nvim-cmp",
        dependencies = {
            "hrsh7th/cmp-nvim-lsp",
            "hrsh7th/cmp-path",
            "hrsh7th/cmp-buffer",
            "hrsh7th/cmp-cmdline",
            "chrisgrieser/cmp-nerdfont",
        },
        config = function()
            local cmp = require'cmp'
            local has_words_before = function()
                unpack = unpack or table.unpack
                local line, col = unpack(vim.api.nvim_win_get_cursor(0))
                return col ~= 0 and vim.api.nvim_buf_get_lines(0, line - 1, line, true)[1]:sub(col, col):match("%s") == nil
            end
            cmp.setup {
                snippet = {
                    expand = function(args)
                        require'luasnip'.lsp_expand(args.body)
                    end
                },
                sources = {
                    { name = "nvim_lsp", priority = 1000, },
                    { name = "luasnip", priority = 850, },
                    { name = "buffer", priority = 750, },
                    { name = "path", priority = 650, },
                    { name = "cmdline", priority = 450, },
                    { name = "nerdfont", priority = 250, },
                },
                mapping = cmp.mapping.preset.insert({
                    ['<C-b>'] = cmp.mapping.scroll_docs(-4),
                    ['<C-f>'] = cmp.mapping.scroll_docs(4),
                    ['<M-j>'] = cmp.mapping.select_next_item(),
                    ['<M-k>'] = cmp.mapping.select_prev_item(),
                    ['<Esc>'] = cmp.mapping.abort(),
                    ['<Tab>'] = cmp.mapping.confirm({ select = true }),
                }),
            }
            cmp.setup.cmdline('/', {
                mapping = cmp.mapping.preset.cmdline(),
                sources = { { name = 'buffer' } }
            })
        end
    },
    {
        "neovim/nvim-lspconfig",
        config = function ()
            local capabilities = require'cmp_nvim_lsp'.default_capabilities()
            local lspconfig = require'lspconfig'
            lspconfig.ccls.setup {
                capabilities = capabilities,
            }
        end
    }
}
