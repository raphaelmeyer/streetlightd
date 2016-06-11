#!/bin/bash

PROJECT_ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

SOURCE="-v ${PROJECT_ROOT}:/home/root/streetlightd:ro"
WORKSPACE=""
# TODO WORKSPACE=--volumes-from ...

docker run -it --rm ${SOURCE} ${WORKSPACE} streetlightd bash

