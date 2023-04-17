#!/bin/bash

rsync -r -e "ssh -i ~/.ssh/Sylos.rsa" --cvs-exclude . tangoway@52.174.37.8:ELI/tango-gateway-framework