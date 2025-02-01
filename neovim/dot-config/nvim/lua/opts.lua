-- Leader
vim.g.mapleader = " "

-- Line numbers
vim.opt.number = true
vim.opt.relativenumber = true

-- Tabs and indentation
vim.opt.tabstop = 2
vim.opt.softtabstop = 2
vim.opt.shiftwidth = 2
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
vim.opt.listchars = { tab = ">>", space = "·", trail = "·", eol = "¬" }

-- Color column
vim.opt.colorcolumn = "80"
