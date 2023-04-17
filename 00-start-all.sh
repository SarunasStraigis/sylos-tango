#!/usr/bin/env bash

pushd $(dirname $0)



./01-init.sh
sleep 2
./03-start-gateway.sh

popd
