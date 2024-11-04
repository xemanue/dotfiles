set -e
set -u

opts=(cancel shutdown reboot logout lock)

declare -A texts
texts[cancel]="Cancel"
texts[shutdown]="Shut down"
texts[reboot]="Reboot"
texts[logout]="Log out"
texts[lock]="Lock"

declare -A comms
comms[cancel]="exit 0"
comms[shutdown]="systemctl poweroff"
comms[reboot]="systemctl reboot"
comms[logout]="loginctl lock-session ${XDG_SESSION_ID-}"
comms[lock]="loginctl lock-session ${XDG_SESSION_ID-}"

echo -en "\0prompt\x1fsys: \n"
for i in "${opts[@]}"
do
    echo -e "${texts[$i]}"
done

for i in "${opts[@]}"
do
    if [ "$@" = "${opts[$i]}" ]
    then
        echo "Selected $i" >$2
        ${comms[$i]}
    fi
done
