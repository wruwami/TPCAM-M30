#!/bin/bash

/home/firefly/command_change.sh
xinput set-prop 'TSC2007 Touchscreen' 'libinput Calibration Matrix' 1.09 0 -0.05 0 1.15 -0.10 0 0 1
echo "touchscreen applied"
cpufreq-set -c 0 1 2 3 -u 1.5Ghz -g performance
cpufreq-set -c 4 5 -u 1.5Ghz -g performance
