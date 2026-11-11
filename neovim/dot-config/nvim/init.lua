local o = vim.o
local g = vim.g
local k = vim.keymap
local c = vim.cmd


--===========================================================================--
-- General config
--===========================================================================--

-- Leaders
g.mapleader = " "
g.maplocalleader = "\\"

-- Line numbers
o.number = true
o.relativenumber = true

-- Always show sign column (left of line numbers)
o.signcolumn = "yes"

-- Mouse support
o.mouse = "a"

-- Don't show mode, ruler or commandline
o.showmode = false
o.ruler = false
o.cmdheight = 0

-- Sync system clipboard
o.clipboard = "unnamedplus"

-- Use undo-file
o.undofile = true

-- Indent wrapped lines (I think)
o.breakindent = true

-- Case insensitive search unless using caps
o.ignorecase = true
o.smartcase = true

-- Enable splits
o.splitright = true
o.splitbelow = true

-- Whitespace display
vim.opt.list = true
vim.opt.listchars = { tab = "--", space = "·", trail = "·", eol = "¬" }

-- Preview substitutions
o.inccommand = "split"

-- Enable cursorline
o.cursorline = true

-- Highlight search
o.hlsearch = true

-- Line wrapping
o.wrap = true

-- Formatting
o.tabstop = 2
o.shiftwidth = 2
o.expandtab = true
o.textwidth = 80

-- Scroll
o.smoothscroll = true
o.scrolloff = 8

-- Automatically 'cd' into opened directory
o.autochdir = true

-- Ask for confirmation when exiting an unsaved buffer
o.confirm = true

-- Diagnostics
vim.diagnostic.config({
  virtual_text = true
})

-- Timeout
o.timeoutlen = 500

-- Conceal level (needed by obsidian.nvim)
o.conceallevel = 1


--===========================================================================--
-- Keymaps
--===========================================================================--

-- General
k.set("n", "<leader>q", "<cmd>q<cr>")
k.set("n", "<leader>w", "<cmd>w<cr>")
k.set("t", "<Esc>", "<C-\\><C-n>")

-- Move lines
k.set("n", "<A-k>", "<cmd>execute 'move .-' . (v:count1 + 1)<cr>==", { desc = "Move Up" })
k.set("n", "<A-j>", "<cmd>execute 'move .+' . v:count1<cr>==", { desc = "Move Down" })
k.set("i", "<A-k>", "<esc><cmd>m .-2<cr>==gi", { desc = "Move Up" })
k.set("i", "<A-j>", "<esc><cmd>m .+1<cr>==gi", { desc = "Move Down" })
k.set("v", "<A-k>", ":<C-u>execute \"'<,'>move '<-\" . (v:count1 + 1)<cr>gv=gv", { desc = "Move Up" })
k.set("v", "<A-j>", ":<C-u>execute \"'<,'>move '>+\" . v:count1<cr>gv=gv", { desc = "Move Down" })

-- Moving up/down takes wrapped lines into consideration
k.set({ "n", "x" }, "j", "v:count == 0 ? 'gj' : 'j'", { desc = "Down", expr = true, silent = true })
k.set({ "n", "x" }, "<Down>", "v:count == 0 ? 'gj' : 'j'", { desc = "Down", expr = true, silent = true })
k.set({ "n", "x" }, "k", "v:count == 0 ? 'gk' : 'k'", { desc = "Up", expr = true, silent = true })
k.set({ "n", "x" }, "<Up>", "v:count == 0 ? 'gk' : 'k'", { desc = "Up", expr = true, silent = true })

-- Split panes
k.set("n", "<leader><C-v>", "<C-w>v", { desc = "Split window vertically" })
k.set("n", "<leader><C-b>", "<C-w>s", { desc = "Split window horizontally" })

-- Moving panes
k.set("n", "<C-h>", "<C-w>h", { desc = "Go to Left Window", remap = true })
k.set("n", "<C-j>", "<C-w>j", { desc = "Go to Lower Window", remap = true })
k.set("n", "<C-k>", "<C-w>k", { desc = "Go to Upper Window", remap = true })
k.set("n", "<C-l>", "<C-w>l", { desc = "Go to Right Window", remap = true })

-- Make panes equal size
k.set("n", "<leader><C-x>", "<C-w>=", { desc = "Make splits equal size" })

-- Resizing panes
k.set("n", "<S-A-h>", "<cmd>vertical resize -2<cr>", { desc = "Increase Pane Height" })
k.set("n", "<S-A-j>", "<cmd>resize -2<cr>", { desc = "Decrease Pane Height" })
k.set("n", "<S-A-k>", "<cmd>resize +2<cr>", { desc = "Increase Pane Width" })
k.set("n", "<S-A-l>", "<cmd>vertical resize +2<cr>", { desc = "Decrease Pane Width" })

-- Close current pane
k.set("n", "<leader><C-c>", "<cmd>close<CR>", { desc = "Close current pane" })

-- Format current buffer
k.set({ "n", "v" }, "<leader>=", vim.lsp.buf.format, { desc = "Format current buffer" })

-- Moving buffers
k.set("n", "<A-h>", "<cmd>bprevious<cr>", { desc = "Prev Buffer" })
k.set("n", "<A-l>", "<cmd>bnext<cr>", { desc = "Next Buffer" })

-- Keep lines selected when indenting in visual mode
k.set("v", "<<", "<gv", { noremap = true, silent = true })
k.set("v", ">>", ">gv", { noremap = true, silent = true })

-- Don't overwrite clipboard when deleting
k.set("v", "p", '"_dP', { noremap = true, silent = true })
k.set({ "n", "v" }, "d", '"_d')
k.set({ "n", "v" }, "s", '"_s')
k.set("n", "x", '"_x', { noremap = true, silent = true })

-- Highlight text when yanking
vim.api.nvim_create_autocmd("TextYankPost", {
  callback = function()
    vim.hl.on_yank()
  end,
})

-- Clear search highlights
k.set("n", "<Esc>", "<cmd>nohlsearch<cr>")


--===========================================================================--
-- Plugins
--===========================================================================--

local plugins = {}

--===========================================================================--
-- Theme

table.insert(plugins, {
  dir = "~/repos/x-mfd.nvim",
  lazy = false,
  priority = 1000,
  config = function()
    require("mfd").setup({
      no_italic = true,
      accesibility_contrast = 10
    })

    vim.cmd.colorscheme('x-mfd-mono')
  end
})


--===========================================================================--
-- Oil

table.insert(plugins, {
  "stevearc/oil.nvim",
  dependencies = { "nvim-tree/nvim-web-devicons" },
  lazy = false,
  keys = {
    { "<leader>-", "<cmd>Oil --float<cr>", desc = "Open file explorer" },
  },
  config = function()
    require("oil").setup({
      view_options = { show_hidden = true },
      float = {
        border = "single",
        max_width = 0.7,
        max_height = 0.6
      },
      -- keymaps_help = { border = "single" },
      keymaps = {
        ["<esc>"] = { "actions.close", mode = "n" },
        ["<C-v>"] = { "actions.select", mode = "n", opts = { vertical = true } },
        ["<C-b>"] = { "actions.select", mode = "n", opts = { horizontal = true } },
      }
    })

    -- vim.api.nvim_set_hl(0, "NormalFloat", { fg = "#d4be98", bg = "#282828" })
    -- vim.api.nvim_set_hl(0, "FloatBorder", { fg = "#7daea3", bg = "#282828" })
    -- vim.api.nvim_set_hl(0, "FloatTitle", { fg = "#282828", bg = "#7daea3" })
  end
})


--===========================================================================--
-- Telescope

table.insert(plugins, {
  "nvim-telescope/telescope.nvim",
  version = "*",
  dependencies = {
    "nvim-lua/plenary.nvim",
    { 'nvim-telescope/telescope-fzf-native.nvim', build = 'make' },
  },
  keys = {
    { "<leader>ff", "<cmd>Telescope find_files<cr>",      desc = "[F]ind [f]iles" },
    { "<leader>fh", "<cmd>Telescope help_tags<cr>",       desc = "[F]ind [h]elp" },
    { "<leader>fg", "<cmd>Telescope live_grep<cr>",       desc = "[F]ind [g]rep" },
    { "<leader>fr", "<cmd>Telescope oldfiles<cr>",        desc = "[F]ind [r]ecent files" },
    { "<leader>fc", "<cmd>Telescope command_history<cr>", desc = "[F]ind [c]ommand history" },
    { "<leader>fm", "<cmd>Telescope marks<cr>",           desc = "[F]ind [m]arks" },
    { "<leader>fp", "<cmd>Telescope highlights<cr>",      desc = "[F]ind [p]ickers" },
  },
  config = function()
    require("telescope").setup({
      defaults = {
        borderchars = { "─", "│", "─", "│", "┌", "┐", "┘", "└" },
        prompt_prefix = "❯ ",
        layout_config = {
          width = 0.7,
          height = 0.6
        },
      },
    })

    vim.api.nvim_set_hl(0, "TelescopeNormal", { link = "NormalFloat" })
    vim.api.nvim_set_hl(0, "TelescopePromptNormal", { link = "NormalFloat" })

    vim.api.nvim_set_hl(0, "TelescopeBorder", { link = "FloatBorder" })
    vim.api.nvim_set_hl(0, "TelescopePromptBorder", { link = "FloatBorder" })

    vim.api.nvim_set_hl(0, "TelescopeTitle", { link = "FloatTitle" })
    vim.api.nvim_set_hl(0, "TelescopePromptTitle", { link = "FloatTitle" })
    vim.api.nvim_set_hl(0, "TelescopeResultsTitle", { link = "FloatTitle" })
  end
})


--===========================================================================--
-- Blink

table.insert(plugins, {
  "saghen/blink.cmp",
  dependencies = { 'rafamadriz/friendly-snippets' },
  version = "1.*",
  event = "InsertEnter",
  opts_extend = { "sources.default" },
  config = function()
    require("blink.cmp").setup({
      keymap = {
        preset = "none",
        ["<A-k>"] = { "select_prev", "fallback" },
        ["<A-j>"] = { "select_next", "fallback" },
        ["<A-l>"] = { "accept", "fallback" },
        ["<A-h>"] = { "show_documentation" },
      },
      completion = {
        list = { max_items = 5 },
        documentation = { auto_show = true, window = { border = "single" } },
      },
      cmdline = {
        keymap = { preset = "inherit" },
        completion = {
          ghost_text = { enabled = false },
          menu = { auto_show = true },
        },
      },
      signature = {
        enabled = false,
        window = { border = "single", show_documentation = false }
      },
      sources = {
        providers = {
          path = {
            opts = {
              show_hidden_files_by_default = true,
            }
          }
        }
      }
    })
  end
})



--===========================================================================--
-- Mini pairs

table.insert(plugins, {
  "nvim-mini/mini.pairs",
  version = false,
  config = function()
    require("mini.pairs").setup({
      modes = {
        command = true,
      },
    })
  end
})


--===========================================================================--
-- LSP config

table.insert(plugins, {
  "neovim/nvim-lspconfig",
  dependencies = { "saghen/blink.cmp" }
})

vim.lsp.config("lua_ls", {
  settings = {
    Lua = {
      telemetry = { enable = false }
    }
  }
})

vim.lsp.config("qs-ls", {
  cmd = { "qml-language-server" },
  filetypes = { "qml" },
  root_markers = { { "qmldir", "shell.qml" }, ".git" },
})

vim.lsp.enable("qs-ls")


--===========================================================================--
-- Mason

table.insert(plugins, {
  "mason-org/mason.nvim",
  keys = {
    { "<leader>m", "<cmd>Mason<cr>", desc = "Open [M]ason" },
  },
  config = function()
    require("mason").setup({
      ui = { border = "single" }
    })
  end
})

table.insert(plugins, {
  "mason-org/mason-lspconfig.nvim",
  opts = {
    ensure_installed = {
      "lua_ls", "bashls", "marksman", "texlab"
    }
  },
  dependencies = {
    { "mason-org/mason.nvim", opts = {} },
    "neovim/nvim-lspconfig",
  },
})


--===========================================================================--
-- Lualine

table.insert(plugins, {
  "nvim-lualine/lualine.nvim",
  dependencies = { "nvim-tree/nvim-web-devicons" },
  config = function()
    local custom = {
      normal = {
        a = { fg = "#1e1e2e", bg = "#89b4fa" },
        b = { fg = "#89b4fa", bg = "#181825" },
        c = { fg = "#cdd6f4", bg = "#11111b" },
      },
      insert = {
        a = { fg = "#1e1e2e", bg = "#a6e3a1" },
        b = { fg = "#a6e3a1", bg = "#181825" },
        c = { fg = "#cdd6f4", bg = "#11111b" },
      },
      visual = {
        a = { fg = "#1e1e2e", bg = "#f38ba8" },
        b = { fg = "#f38ba8", bg = "#181825" },
        c = { fg = "#cdd6f4", bg = "#11111b" },
      },
      command = {
        a = { fg = "#1e1e2e", bg = "#fab387" },
        b = { fg = "#fab387", bg = "#181825" },
        c = { fg = "#cdd6f4", bg = "#11111b" },
      },
      replace = {
        a = { fg = "#1e1e2e", bg = "#cba6f7" },
        b = { fg = "#cba6f7", bg = "#181825" },
        c = { fg = "#cdd6f4", bg = "#11111b" },
      },
      inactive = {
        a = { fg = "#cdd6f4", bg = "#1e1e2e" },
        b = { fg = "#bac2de", bg = "#181825" },
        c = { fg = "#a6adc8", bg = "#11111b" },
      },
    }

    require("lualine").setup({
      options = {
        theme = "mfd-mono",
        component_separators = "|",
        section_separators = "",
      },
      sections = {
        lualine_c = { { "filename", separator = "" } },
        lualine_x = { "filetype" },
      },
      inactive_sections = {
        lualine_a = { "mode" },
        lualine_b = { "branch", "diff", "diagnostics" },
        lualine_c = { { "filename", separator = "" } },
        lualine_x = { "filetype" },
        lualine_y = { "progress" },
        lualine_z = { "location" },
      },
      extensions = { "lazy", "man", "mason", "oil" }
    })
  end
})


--===========================================================================--
-- Bufferline

table.insert(plugins, {
  "akinsho/bufferline.nvim",
  version = "*",
  dependencies = "nvim-tree/nvim-web-devicons",
  config = function()
    local bufferline = require("bufferline")
    bufferline.setup {
      options = {
        style_preset = bufferline.style_preset.no_italic,
        themable = true,
        right_mouse_command = nil,
        middle_mouse_command = "bdelete! %d",
        tab_size = 16,
        indicator = { style = "none" },
        separator_style = { "", "" },
        show_buffer_close_icons = false,
        show_buffer_icons = false,
        diagnostics = false,
        left_trunc_marker = "",
        right_trunc_marker = "",
        hover = { enabled = false },
        enforce_regular_tabs = true,
      }
    }

    vim.api.nvim_set_hl(0, "BufferLineFill", { bg = "#08080c" })
    --
    -- vim.api.nvim_set_hl(0, "BufferLineBufferSelected", { fg = "#282828", bg = "#a89984" } )
    -- vim.api.nvim_set_hl(0, "BufferLineModifiedSelected", { fg = "#282828", bg = "#a89984" } )
    -- vim.api.nvim_set_hl(0, "BufferLineModifiedVisible", { fg = "#d4be98", bg = "#504945" } )
    -- vim.api.nvim_set_hl(0, "BufferLineIndicatorSelected", { fg = "#282828", bg = "#a89984" } )
    -- vim.api.nvim_set_hl(0, "BufferLineIndicatorVisible", { fg = "#d4be98", bg = "#504945" } )
    --
    -- vim.api.nvim_set_hl(0, "BufferLineBackground", { fg = "#d4be98", bg = "#504945" } )
    -- vim.api.nvim_set_hl(0, "BufferLineBufferVisible", { fg = "#d4be98", bg = "#504945" } )
    -- vim.api.nvim_set_hl(0, "BufferLineModified", { fg = "#d4be98", bg = "#504945" } )
  end
})


--===========================================================================--
-- Noice

table.insert(plugins, {
  "folke/noice.nvim",
  event = "VeryLazy",
  dependencies = { "MunifTanjim/nui.nvim" },
  config = function()
    require("noice").setup({
      cmdline = {
        opts = { border = { style = "single" }, },
        format = {
          cmdline = { icon = "❯", icon_hl_group = "NoiceCmdlinePrompt" },
          search_down = { icon = " ", icon_hl_group = "NoiceCmdlinePrompt" },
          search_up = { icon = " ", icon_hl_group = "NoiceCmdlinePrompt" },
        }
      },
      lsp = {
        signature = {
          enabled = true,
          opts = {
            border = { style = "single" },
            size = { width = 40, height = 10 },
            position = { row = 2, col = 0 },
          },
        },
      },
      routes = {
        {
          filter = { event = "msg_show", kind = "search_count" },
          opts = { skip = true },
        },
      },
    })

    vim.api.nvim_set_hl(0, "NoiceCmdlinePopup", { link = "NormalFloat" })
    vim.api.nvim_set_hl(0, "NoiceCmdlinePopupBorder", { link = "FloatBorder" })
    vim.api.nvim_set_hl(0, "NoiceCmdlinePopupTitleCmdline", { link = "FloatTitle" })

    vim.api.nvim_set_hl(0, "NoiceCmdlinePopupTitleLua", { link = "FloatTitle" })

    vim.api.nvim_set_hl(0, "NoiceCmdlinePopupBorderSearch", { link = "FloatBorder" })
    vim.api.nvim_set_hl(0, "NoiceCmdlinePopupTitleSearch", { link = "FloatTitle" })
    --
    --
  end
})


--===========================================================================--
-- To do's

table.insert(plugins, {
  "folke/todo-comments.nvim",
  dependencies = { "nvim-lua/plenary.nvim",
    "nvim-telescope/telescope.nvim"
  },
  keys = {
    { "<leader>ft", "<cmd>TodoTelescope<cr>", desc = "[F]ind [t]o do\'s" },
  },
  config = function()
    require("todo-comments").setup()
  end
})


--===========================================================================--
-- Mini starter

table.insert(plugins, {
  "nvim-mini/mini.starter",
  version = false,
  config = function()
    local starter = require("mini.starter")

    starter.setup({
      items = {
        {
          name = "init.lua",
          action = "e $HOME/.config/nvim/init.lua",
          section = "Common",
        },
        {
          name = "Obsidian vault",
          action = "e $HOME/documents/vault/",
          section = "Common",
        },
        { starter.sections.recent_files(5, false) },
        {
          name = "Lazy - Update plugins",
          action = "lua require('lazy').update({ show = false })",
          section = "Misc actions"
        },
      },
    })
  end
})


--===========================================================================--
-- Mini surround

table.insert(plugins, {
  "nvim-mini/mini.surround",
  version = false,
  config = function()
    require("mini.surround").setup()
  end
})


--===========================================================================--
-- Obsidian

table.insert(plugins, {
  "epwalsh/obsidian.nvim",
  version = "*",
  lazy = true,
  event = {
    "BufReadPre " .. vim.fn.expand "~" .. "/Documents/Vault/*.md",
    "BufNewFile " .. vim.fn.expand "~" .. "/Documents/Vault/*.md",
  },
  dependencies = {
    "nvim-lua/plenary.nvim",
  },
  config = function()
    require("obsidian").setup({
      workspaces = {
        {
          name = "vault",
          path = "~/Documents/Vault",
        },
      },
    })
  end
})


--===========================================================================--
-- VimTex

table.insert(plugins, {
  "lervag/vimtex",
  lazy = false,
  init = function()
    vim.g.vimtex_view_general_viewer = "okular"
  end
})

--===========================================================================--
-- WhichKey

table.insert(plugins, {
  "folke/which-key.nvim",
  event = "VeryLazy",
  opts = {
    preset = "helix",
    plugins = {
      spelling = { enabled = false },
    },
    win = {
      border = "single",
    },
    icons = {
      separator = "-",
      mappings = false,
    },
  },
  keys = {
    {
      "<leader>?",
      function()
        require("which-key").show({ global = false })
      end,
      desc = "Buffer Local Keymaps (which-key)",
    },
  },
})


--===========================================================================--
-- Lazy

k.set({ "n" }, "<leader>l", "<cmd>Lazy<cr>", { desc = "Open [L]azy" })

-- Bootstrap lazy.nvim
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not (vim.uv or vim.loop).fs_stat(lazypath) then
  local lazyrepo = "https://github.com/folke/lazy.nvim.git"
  local out = vim.fn.system({ "git", "clone", "--filter=blob:none", "--branch=stable", lazyrepo, lazypath })
  if vim.v.shell_error ~= 0 then
    vim.api.nvim_echo({
      { "Failed to clone lazy.nvim:\n", "ErrorMsg" },
      { out,                            "WarningMsg" },
      { "\nPress any key to exit..." },
    }, true, {})
    vim.fn.getchar()
    os.exit(1)
  end
end
vim.opt.rtp:prepend(lazypath)

-- Setup lazy.nvim
require("lazy").setup({
  spec = { plugins },
  -- Configure any other settings here. See the documentation for more details.
  -- colorscheme that will be used when installing plugins.
  install = { colorscheme = { "gruvbox-material" } },
  -- automatically check for plugin updates
  checker = { enabled = true },
  ui = {
    size = {
      width = 0.6,
      height = 0.7,
    },
    border = "single",
  },
})
