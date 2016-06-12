#!/bin/bash

VERSION=latest

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

SRC_HOST=${DIR}/source
SRC_GUEST=/home/user/source

WORKSPACE=`./workspace.sh "raspbian"`

VOLUMES="--volumes-from ${WORKSPACE} -v ${SRC_HOST}:${SRC_GUEST}:ro"
CONTAINER="streetlightd-raspbian:${VERSION}"

