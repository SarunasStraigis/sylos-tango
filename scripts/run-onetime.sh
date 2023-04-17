#!/bin/bash

echo "Don't forget to start the services: sudo service monit start"
docker run \
    -e TANGO_HOST=$(hostname --short):10000\
    -e PYTHONPATH=/home/tangouser/ELI/tango-gateway-framework/src\
    -it \
    --rm\
    -v ~/ELI:/home/tangouser/ELI\
    --net host\
    --name tango9\
    tango9\
    bash
