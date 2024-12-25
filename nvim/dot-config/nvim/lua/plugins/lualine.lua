return
{
    'nvim-lualine/lualine.nvim',
    dependencies = { 'nvim-tree/nvim-web-devicons' },
    config = function()
        require('lualine').setup({
            options = {
        		icons_enabled = true,
                theme = "auto", -- or 'dracula', 'tokyonight', or your preferred theme
        		component_separators = { left = "|", right = "|" },
        		globalstatus = true,
        	},
            sections = {
        		lualine_a = { { "mode", upper = true } },
        		lualine_b = { "branch", "diff" },
        		lualine_c = { { "filename", file_status = true, path = 0 }, } ,
        		lualine_x = {
    			    "encoding",
    			    "filetype",
        		},
        		lualine_y = { "progress" },
        		lualine_z = { "location" },
        	},
        	inactive_sections = {
        		lualine_a = {},
        		lualine_b = {},
        		lualine_c = { { "filename", file_status = true, path = 1 } },
        		lualine_x = { "location" },
        		lualine_y = {},
        		lualine_z = {},
        	},
        	tabline = {},
        	extensions = { "lazy", "man", "neo-tree" }
        })

        vim.opt.showmode = false
    end
}
