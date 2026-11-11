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
alias ff="fastfetch"
alias clear="clear && fastfetch"
alias :q="exit"

# Eza
alias ls='eza -al --icons --color=always --group-directories-first' # preferred listing
alias la='eza -a --icons --color=always --group-directories-first' # all files and dirs
alias ll='eza --icons -l --color=always --group-directories-first' # long format
alias lt='eza --icons -aT --color=always --group-directories-first' # tree listing
alias l.="eza --icons -a --color=always --group-directories-first | grep -e '^\.'" # show only dotfiles

# Git
alias gs="git status"
alias gd="git diff --output-indicator-new=' ' --output-indicator-old=' '"
alias gds="git diff --staged"
alias ga="git add"
alias gap="git add --patch"
alias gc="git commit"
alias gp="git push"
alias gu="git pull"
alias gl="git log --graph --all --pretty=format:'%C(cyan)%h %C(brightwhite)%an %C(brightblack)%ar %C(auto) %D%n%s%n'"
alias gb="git branch"
alias gco="git checkout"
alias gi="git init"
alias gcl="git clone"

function gr
  set -l up (git rev-parse --show-cdup)
  test -n "$up"; and cd $up
end

# alias gr='if [ "`git rev-parse --show-cdup`" != "" ]; then cd `git rev-parse --show-cdup`; fi'


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
