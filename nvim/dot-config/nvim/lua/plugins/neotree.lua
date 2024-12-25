return
{
    "nvim-neo-tree/neo-tree.nvim",
    branch = "v3.x",
    dependencies =
    {
        "nvim-lua/plenary.nvim",
        "nvim-tree/nvim-web-devicons",
        "MunifTanjim/nui.nvim"
    },
	config = function()
        require("neo-tree").setup({
            close_if_last_window = true,

            filesystem = {
                bind_to_cwd = true,
                filtered_items = {
                    visible = true,
                },
            },
            window = {
                width = 30,
                mappings = {
                    ["l"] = "open",
                    ["h"] = "close_node",
                },
            },
        })

		vim.keymap.set("n", "<leader>b", ":Neotree toggle filesystem left<CR>", {})
	end
}
