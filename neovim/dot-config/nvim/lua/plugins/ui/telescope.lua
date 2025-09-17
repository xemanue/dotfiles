return {
    'nvim-telescope/telescope.nvim',
    tag = '0.1.8',
    dependencies = { 'nvim-lua/plenary.nvim' },
    config = function ()
        require("telescope").setup({
            defaults = {
                borderchars = { "─", "│", "─", "│", "┌", "┐", "┘", "└" },
                prompt_prefix = " ",
            },
        })

        local builtin = require("telescope.builtin")

        vim.keymap.set("n", "<leader>ff", builtin.find_files, { desc = "[F]ind [F]iles" })
        vim.keymap.set("n", "<leader>fr", builtin.oldfiles, { desc = "[F]ind [R]ecent files" })
        vim.keymap.set("n", "<leader>fg", builtin.live_grep, { desc = "[F]ind [G]rep" })
        vim.keymap.set("n", "<leader>fh", builtin.help_tags, { desc = "[F]ind [H]elp" })
        vim.keymap.set("n", "<leader>fm", builtin.marks, { desc = "[F]ind [M]arks" })
        vim.keymap.set("n", "<leader>fc", builtin.command_history, { desc = "[F]ind [C]ommand history" })
        vim.keymap.set("n", "<leader>fp", builtin.pickers, { desc = "[F]ind [P]ickers" })
    end
}
