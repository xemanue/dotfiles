alias ff="fastfetch"
alias clear="clear && fastfetch"
alias :q="exit"

# Easy backup
function bak --argument filename
    cp $filename $filename.bak
end

#------------------------------------------------------------------------------
# Eza

alias ls='eza --icons --color=always --group-directories-first' # Default
alias la='eza -la --icons --color=always --group-directories-first' # -la
alias ll='eza --icons -l --color=always --group-directories-first' # Long format
alias lt='eza --icons -aT --color=always --group-directories-first' # Tree
alias l.="eza --icons -a --color=always --group-directories-first | grep -e '^\.'"
  # Dotfiles

#------------------------------------------------------------------------------
# Git

alias gs="git status"
alias gd="git diff --output-indicator-new=' ' --output-indicator-old=' '"
alias gds="git diff --staged"
alias ga="git add"
alias gap="git add --patch"
alias gc="git commit"
alias gp="git push"
alias gu="git pull"
alias gl="git log --graph --all \
  --pretty=format:'%C(cyan)%h %C(brightwhite)%an %C(brightblack)%ar %C(auto) \
  %D%n%s%n'"
alias gb="git branch"
alias gco="git checkout"
alias gi="git init"
alias gcl="git clone"

function gr
  set -l up (git rev-parse --show-cdup)
  test -n "$up"; and cd $up
end
