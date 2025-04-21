return {
    "sainnhe/gruvbox-material",
    enabled = true,
    lazy = false,
    priority = 1000,
    config = function()
        vim.g.gruvbox_material_background = "soft"
        vim.cmd.colorscheme("gruvbox-material")
    end
}
