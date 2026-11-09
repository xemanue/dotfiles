source ~/.config/fish/binds.fish

function fish_greeting
    fastfetch
end

# Format man pages
set -x MANROFFOPT "-c"
set -x MANPAGER "nvim +Man!"

# Enable MangoHud
set -x MANGOHUD 1

# Add ~/.local/bin to PATH
if test -d ~/.local/bin
    if not contains -- ~/.local/bin $PATH
        set -p PATH ~/.local/bin
    end
end

## Aliases
# Eza
alias ls='eza -al --icons --color=always --group-directories-first' # preferred listing
alias la='eza -a --icons --color=always --group-directories-first' # all files and dirs
alias ll='eza --icons -l --color=always --group-directories-first' # long format
alias lt='eza --icons -aT --color=always --group-directories-first' # tree listing
alias l.="eza --icons -a --color=always --group-directories-first | grep -e '^\.'" # show only dotfiles
alias ff="fastfetch"
alias clear="clear && fastfetch"
alias :q="exit"

## Functions
# Functions needed for !! and !$ https://github.com/oh-my-fish/plugin-bang-bang
function __history_previous_command
  switch (commandline -t)
  case "!"
    commandline -t $history[1]; commandline -f repaint
  case "*"
    commandline -i !
  end
end

function __history_previous_command_arguments
  switch (commandline -t)
  case "!"
    commandline -t ""
    commandline -f history-token-search-backward
  case "*"
    commandline -i '$'
  end
end

if [ "$fish_key_bindings" = fish_vi_key_bindings ];
  bind -Minsert ! __history_previous_command
  bind -Minsert '$' __history_previous_command_arguments
else
  bind ! __history_previous_command
  bind '$' __history_previous_command_arguments
end

# Easy backup
function bak --argument filename
    cp $filename $filename.bak
end

starship init fish | source
