-- Leader
vim.g.mapleader = " "

-- Line numbers
vim.opt.number = true
vim.opt.relativenumber = true

-- Tabs and indentation
vim.opt.tabstop = 4
vim.opt.softtabstop = 4
vim.opt.shiftwidth = 4
vim.opt.expandtab = true

-- Line wrap
vim.opt.wrap = true
vim.opt.linebreak = true

-- Search
vim.opt.hlsearch = true
vim.opt.incsearch = true

-- Scrolloff
vim.opt.scrolloff = 2

-- Clipboard
vim.cmd("set clipboard+=unnamedplus")

-- Misc
vim.opt.swapfile = false
vim.opt.backup = false
vim.opt.undofile = true
vim.opt.autochdir = true

vim.g.loaded_netrwPlugin = true
vim.g.loaded_netrw = true

-- Visible whitespace
vim.opt.list = true
vim.opt.listchars = { tab = "> ", space = "·", trail = "·", eol = "¬" }

-- Color column
vim.opt.colorcolumn = "80"

-- Insert Mode hjkl binds
vim.keymap.set("i", "<M-h>", "<left>", {})
vim.keymap.set("i", "<M-j>", "<down>", {})
vim.keymap.set("i", "<M-k>", "<up>", {})
vim.keymap.set("i", "<M-l>", "<right>", {})

-- Make search case insensitive
vim.opt.ignorecase = true
