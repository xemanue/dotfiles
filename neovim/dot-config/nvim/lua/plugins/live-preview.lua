return {
    "brianhuster/live-preview.nvim",
    dependencies = {
        'nvim-telescope/telescope.nvim',
    },

    opts = {
        browser = '/home/xema/.local/share/AppImage/ZenBrowser.AppImage %u -P "Default"',
    },

    config = function ()
		vim.keymap.set("n", "<leader>p", ":LivePreview start<CR>", {})
    end
}
