#!/bin/bash

if [[ $(xset q | grep -i "caps" | awk '{print $4}') == *on* ]]; then
        echo -n "%{F#f38ba8}CL"
else
        echo -n "%{F#6c7086}CL"
fi
