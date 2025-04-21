return {
    "catppuccin/nvim",
    enabled = false,
    name = "catppuccin",
    lazy = false,
    priority = 1000,
    opts = {
        flavour = "frappe",
        integrations = {
            mini = {
                enabled = true,
            },
            snacks = {
                enabled = true,
            },
            telescope = {
                enabled = true,
            },
        }
    }
}
