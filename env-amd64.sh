#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

SRC_HOST=${DIR}/source
SRC_GUEST=/home/user/source

WORKSPACE=`./workspace.sh "amd64"`

VOLUMES="--volumes-from ${WORKSPACE} -v ${SRC_HOST}:${SRC_GUEST}:ro"
CONTAINER="streetlight-amd64:${AMD64}"

