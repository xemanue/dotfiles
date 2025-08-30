-- Line numbers
vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.signcolumn = "yes"

-- Line highlight
vim.opt.cursorline = true

-- Tabs and indentation
vim.opt.tabstop = 4
vim.opt.softtabstop = 4
vim.opt.shiftwidth = 4
vim.opt.expandtab = true
vim.opt.autoindent = true
vim.opt.smartindent = true
vim.opt.backspace = { "indent", "eol", "start" }

-- Line wrap
vim.opt.wrap = true
vim.opt.linebreak = true

-- Search
vim.opt.incsearch = true
vim.opt.ignorecase = true
vim.opt.smartcase = true
vim.opt.hlsearch = true

-- Clipboard
vim.opt.clipboard:append("unnamedplus")

-- Scroll
vim.opt.smoothscroll = true
vim.opt.scrolloff = 8

-- Visible whitespace
vim.opt.list = true
vim.opt.listchars = { tab = "--", space = "·", trail = "·", eol = "¬" }

-- Splits
vim.opt.splitright = true
vim.opt.splitbelow = true
vim.opt.splitkeep = "screen"

-- Files
vim.opt.autochdir = true
vim.opt.confirm = true -- Confirm to save changes before exiting modified buffer
vim.opt.grepprg = "rg --vimgrep"
vim.opt.swapfile = false
vim.opt.backup = false
vim.opt.undofile = true

-- Colors
vim.opt.termguicolors = true
vim.opt.background = "dark"

-- Bar
vim.opt.showmode = false
vim.opt.ruler = false
vim.opt.cmdheight = 0

-- Time
vim.opt.updatetime = 200
vim.opt.timeoutlen = 500

-- Mouse
vim.opt.mouse = "a"

-- Misc
-- vim.opt.conceallevel = 1
