#!/usr/bin/env bash

echo "Start Gateway"
d=$(dirname $0)
${d}/src/laser_system/laser_gatewayDS.py lc &
