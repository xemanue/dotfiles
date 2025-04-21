return {
    {
        "folke/snacks.nvim",
        opts = {
            dashboard = {
                enabled = true,
                preset = {
                    header = [[
▗▖  ▗▖▗▞▀▚▖ ▄▄▄  ▄   ▄ ▄ ▄▄▄▄ 
▐▛▚▖▐▌▐▛▀▀▘█   █ █   █ ▄ █ █ █
▐▌ ▝▜▌▝▚▄▄▖▀▄▄▄▀  ▀▄▀  █ █   █
▐▌  ▐▌                 █      ]],
                    keys = {
                        { icon = "󰈈 ", key = "-", desc = "View Files", action = ":Oil --float" },
                        { icon = " ", key = "n", desc = "New File", action = ":ene | startinsert" },
                        { icon = " ", key = "f", desc = "Find File", action = ":lua Snacks.dashboard.pick('files')" },
                        { icon = " ", key = "/", desc = "Find Text", action = ":lua Snacks.dashboard.pick('live_grep')" },
                        { icon = " ", key = "r", desc = "Recent Files", action = ":lua Snacks.dashboard.pick('oldfiles')" },
                        { icon = " ", key = "r", desc = "Restore Session", section = "session" },
                        { icon = "󰒲 ", key = "l", desc = "Lazy", action = ":Lazy", enabled = package.loaded.lazy ~= nil },
                        { icon = " ", key = "q", desc = "Quit", action = ":qa" }
                    },
                },
                sections = {
                    {
                        { section = "header" },
                        { section = "keys", padding = 1 },
                        { section = "startup" },
                    },
                }
            },
            picker = {
                layout = {
                    width = 0.5,
                    height = 0.5,
                    {
                        border = "single",
                    },
                },
            },
        }
    }
}
