#!/bin/bash

script_dir="$(cd "$(dirname "$0")" && pwd)"
target_script="command_change.sh"
target_script_path="$script_dir/$target_script"
if [ -e "$target_script_path" ]; then
	source "$target_script_path"
else
	echo "The target script does not exist: $target_script_path"
fi
xinput set-prop 'TSC2007 Touchscreen' 'libinput Calibration Matrix' 1.09 0 -0.05 0 1.15 -0.10 0 0 1
echo "touchscreen applied"
cpufreq-set -c 0 1 2 3 -u 1.2Ghz -g performance
cpufreq-set -c 4 5 -u 1.2Ghz -g performance

cursor_text_content="[Seat:*]
# Dump core
xserver-command=X -core -nocursor
"
echo "$cursor_text_content" > "/usr/share/lightdm/lightdm.conf.d/50-xserver-command.conf"