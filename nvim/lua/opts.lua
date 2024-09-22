local o = vim.opt

-- Leader
vim.g.mapleader = " "

-- Line numbers
o.number = true
o.relativenumber = true

-- Tabs and indentation
o.tabstop = 4
o.softtabstop = 4
o.shiftwidth = 4
o.expandtab = true

-- Line wrap
o.wrap = true

-- Search
o.hlsearch = true
o.incsearch = true

-- Scrolloff
o.scrolloff = 3

-- Clipboard
vim.cmd("set clipboard+=unnamedplus")

-- Misc
o.swapfile = false
o.backup = false
o.undofile = true
