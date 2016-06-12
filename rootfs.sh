#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

NAME="rootfs"
IMAGE="raphaelmeyer/rootfs:1.0.0"

rm -rf ${DIR}/rootfs
mkdir -p ${DIR}/rootfs

ROOTFS=`${DIR}/workspace-id.sh ${NAME} ${IMAGE}`

if [ ! -z ${ROOTFS} ] ; then
  echo "Delete ${ROOTFS}"
  docker rm -v ${ROOTFS}
fi

ROOTFS=`${DIR}/workspace.sh ${NAME} ${IMAGE}`

rsync -rl --delete-after --safe-links pi@rpi2_blue:/{lib,usr} ${DIR}/rootfs

docker cp rootfs/lib ${ROOTFS}:/rootfs
docker cp rootfs/usr ${ROOTFS}:/rootfs

