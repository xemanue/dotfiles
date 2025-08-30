return {
    "epwalsh/obsidian.nvim",
    enabled = false,
    version = "*", -- recommended, use latest release instead of latest commit
    lazy = true,
    ft = "markdown",
    dependencies = {
        "nvim-lua/plenary.nvim",
    },
    opts = {
        workspaces = {
            {
                name = "obsidian",
                path = "~/documents/obsidian/",
            },
        },
        daily_notes = {
            folder = "99. Dailies",
            -- Optional, default tags to add to each new daily note created.
            default_tags = { "Daily" },
            -- Optional, if you want to automatically insert a template from your template directory like 'daily.md'
            template = "{{date}}.md",
        },
        templates = {
            folder = "98. Templates",
        },
        picker = {
            -- Set your preferred picker. Can be one of 'telescope.nvim', 'fzf-lua', or 'mini.pick'.
            name = "fzf-lua",
        },
        mappings = {
            ["<C-_>"] = {
                action = function()
                    return require("obsidian").util.smart_action()
                end,
                opts = { buffer = true, expr = true },
            },
        },
    },
}
