#!/bin/bash

VERSION=latest

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

SRC_HOST=${DIR}/source
SRC_GUEST=/home/user/source

WORKSPACE=`./workspace.sh "raspbian"`
ROOTFS=`./workspace.sh "rootfs" "raphaelmeyer/rootfs:1.0.0"`

VOLUMES="--volumes-from ${WORKSPACE} --volumes-from ${ROOTFS} -v ${SRC_HOST}:${SRC_GUEST}:ro"
CONTAINER="streetlightd-raspbian:${VERSION}"

