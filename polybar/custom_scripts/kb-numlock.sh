#!/bin/bash

if [[ $(xset q | grep -i "num" | awk '{print $8}') == *on* ]]; then
        echo -n "%{F#f38ba8}NL"
else
        echo -n "%{F#6c7086}NL"
fi
