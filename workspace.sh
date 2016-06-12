#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

if [ $# -lt 1 ] ; then
  echo "Missing workspace name"
  exit 1
fi

IMAGE=raphaelmeyer/base:1.1.0
NAME="${1}.id"
WS_DIR=${DIR}/workspaces
FILE=${WS_DIR}/${NAME}

if [ $# -ge 2 ] ; then
  IMAGE=$2
fi

ID=`${DIR}/workspace-id.sh ${1} ${IMAGE}`

if [ ! -z ${ID} ] ; then
  echo ${ID}
  exit 0
fi

ID=$(docker create ${IMAGE})
echo $ID > ${FILE}
echo ${ID}

