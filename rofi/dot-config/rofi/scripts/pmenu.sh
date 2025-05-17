#!/usr/bin/env bash

# Current Theme
dir="$HOME/.config/rofi/styles"
theme='pmenu'

# CMDs
uptime="`uptime | sed -E 's/^[^,]*up *//; s/, *[[:digit:]]* user(s)?.*//; s/ min/m/; s/([[:digit:]]+):0?([[:digit:]]+)/\1h \2m/; s/ day(s)?,/d/'`"
host=`hostname`

# Options
shutdown=''
reboot=''
sleep=''
logout=''
yes=''
no=''

# Rofi CMD
rofi_cmd() {
	rofi -dmenu \
		-p "Uptime $uptime" \
		-mesg "Uptime $uptime" \
		-theme ${dir}/${theme}.rasi
}

# Confirmation CMD
confirm_cmd() {
	rofi -dmenu \
		-p 'Confirm?' \
		-mesg 'Confirm?' \
		-theme ${dir}/pmenu_confirm.rasi
}

# Ask for confirmation
confirm_exit() {
	echo -e "$yes\n$no" | confirm_cmd
}

# Pass variables to rofi dmenu
run_rofi() {
	echo -e "$sleep\n$logout\n$reboot\n$shutdown" | rofi_cmd
}

# Execute Command
run_cmd() {
	selected="$(confirm_exit)"
	if [[ "$selected" == "$yes" ]]; then
		if [[ $1 == '--shutdown' ]]; then
			systemctl poweroff
		elif [[ $1 == '--reboot' ]]; then
			systemctl reboot
        elif [[ $1 == '--sleep' ]]; then
            systemctl suspend
		elif [[ $1 == '--logout' ]]; then
            hyprctl dispatch exit
		fi
	else
		exit 0
	fi
}

# Actions
chosen="$(run_rofi)"
case ${chosen} in
    $shutdown)
		run_cmd --shutdown
        ;;
    $reboot)
		run_cmd --reboot
        ;;
    $sleep)
        run_cmd --sleep
        ;;
    $logout)
		run_cmd --logout
        ;;
esac
