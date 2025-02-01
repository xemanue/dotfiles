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
      "hrsh7th/cmp-emoji",
      "SergioRibera/cmp-dotenv",
      "chrisgrieser/cmp-nerdfont",
    },
    config = function()
      local cmp = require'cmp'
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
          { name = "codeium", priority = 550, },
          { name = "cmdline", priority = 450, },
          { name = "dotenv", priority = 350, },
          { name = "nerdfont", priority = 250, },
          { name = "emoji", priority = 150, },
        },
        mapping = cmp.mapping.preset.insert({
          ['<C-b>'] = cmp.mapping.scroll_docs(-4),
          ['<C-f>'] = cmp.mapping.scroll_docs(4),
          ['<C-Space>'] = cmp.mapping.complete(),
          ['<C-e>'] = cmp.mapping.abort(),
          ['<CR>'] = cmp.mapping.confirm({ select = false }),
        }),
      }
    end
  }
}
