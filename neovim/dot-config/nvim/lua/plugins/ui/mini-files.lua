return {
    'echasnovski/mini.files',
    version = false,
    lazy = false,
    opts = {
        mappings = {
            synchronize = "<C-enter>"
        },
        windows = {
            width_nofocus = 25,
        },
    },
    keys = {
        {
            "<leader>-",
            function()
                local files = require("mini.files")
                if not files.close() then files.open() end
            end
        },
        { "<esc>", function() require("mini.files").close() end },
        { "<enter>", function() require("mini.files").go_in({ close_on_file = false }) end },
        { "<S-enter>", function() require("mini.files").go_in({ close_on_file = true }) end },
    },
    --[[
    config = function(_, opts)
        local map_split = function(buf_id, lhs, direction, close_on_file)
            local rhs = function()
                local new_target_window
                local cur_target_window = require("mini.files").get_explorer_state().target_window
                if cur_target_window ~= nil then
                    vim.api.nvim_win_call(
                        cur_target_window, function()
                            vim.cmd("belowright " .. direction .. " split")
                            new_target_window = vim.api.nvim_get_current_win()
                        end
                    )

                    require("mini.files").set_target_window(new_target_window)
                    require("mini.files").go_in({ close_on_file = close_on_file })
                end
            end

            local desc = "Open in " .. direction .. " split"
            if close_on_file then
                desc = desc .. " and close"
            end

            vim.keymap.set("n", lhs, rhs, { buffer = buf_id, desc = desc })
        end

        vim.api.nvim_create_autocmd("User", {
            pattern = "MiniFilesBufferCreate",
            callback = function(args)
                local buf_id = args.data.buf_id

                vim.keymap.set(
                    "n",
                    opts.mappings and opts.mappings.toggle_hidden or "g.",
                    toggle_dotfiles,
                    { buffer = buf_id, desc = "Toggle hidden files" }
                )

                vim.keymap.set(
                    "n",
                    opts.mappings and opts.mappings.change_cwd or "gc",
                    files_set_cwd,
                    { buffer = args.data.buf_id, desc = "Set cwd" }
                )

                map_split(buf_id, opts.mappings and opts.mappings.go_in_horizontal or "<leader>sb", "horizontal", false)
                map_split(buf_id, opts.mappings and opts.mappings.go_in_vertical or "<leader>sv", "vertical", false)
                map_split(buf_id, opts.mappings and opts.mappings.go_in_horizontal_plus or "<leader>sB", "horizontal", true)
                map_split(buf_id, opts.mappings and opts.mappings.go_in_vertical_plus or "<leader>sV", "vertical", true)
            end,
        }) 
    end
    ]]--
}
