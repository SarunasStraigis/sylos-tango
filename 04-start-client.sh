#!/usr/bin/env bash

echo "Start client"
d=$(dirname $0)
${d}/src/laser_system/laser_gatewayCLIENT.py
