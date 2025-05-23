vim.uv = vim.uv or vim.loop

local M = {}

function M.setup(opts)
	require("lazyvim.config").setup(opts)
end

return M
