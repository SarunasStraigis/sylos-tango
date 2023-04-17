#!/bin/bash

docker run \
    -e TANGO_HOST=$(hostname --short):10000\
    -e PYTHONPATH=/home/tangouser/ELI/tango-gateway-framework/src \
    --detach
    --volume ~/ELI:/home/tangouser/ELI
    --net host
    --name tango9
    tango9
docker ps
echo "Connect with 'docker exec -it tango9 bash'"