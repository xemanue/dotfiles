#!/usr/bin/env bash
config_dir="${XDG_CONFIG_HOME:-$HOME/.config}/wlr-which-key"
config_temp="$config_dir/config-template.yaml"
colors_file="$config_dir/matugen.yaml"

out_file="$config_dir/config.yaml"

cat "$config_temp" > "$out_file"
echo -e "" >> "$out_file"
cat "$colors_file" >> "$out_file"
