return {
    "nvim-treesitter/nvim-treesitter",
    build = ":TSUpdate",
    config = function()
        local treesitter = require("nvim-treesitter")
        treesitter.setup()
        treesitter.install{ "c", "cpp", "lua", "python", "bash", "rust",
                    "vim", "vimdoc", "html", "css", "json" }

        vim.api.nvim_create_autocmd("FileType", {
            pattern = { "c", "cpp", "lua", "python", "bash", "rust",
                      "vim", "vimdoc", "html", "css", "json" },
            callback = function()
                vim.treesitter.start()
                vim.bo.indentexpr = "v:lua.require'nvim-treesitter'.indentexpr()"
            end,
        })
    end
}
