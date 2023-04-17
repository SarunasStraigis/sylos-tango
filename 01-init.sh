#!/usr/bin/env bash

echo "Initialize Tango DB"
d=$(dirname $0)
${d}/util/db_loader.py -n "laser/gateway/1" -d "LaserGateway" -s "laser_gatewayDS/lc"
