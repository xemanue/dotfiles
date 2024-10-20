#!/bin/bash
echo -n "%{F#f38ba8}"; localectl status | grep "X11" | awk 'NF>1{print toupper($NF)}'
