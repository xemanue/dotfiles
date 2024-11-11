return
{
	"mellow-theme/mellow.nvim",
    enabled = true,
	name = "mellow",
	priority = 1000,
    config = function()
        vim.cmd.colorscheme "mellow"
        vim.g.mellow_italic_comments = false
    end
}
