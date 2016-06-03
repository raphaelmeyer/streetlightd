#!/bin/bash

cmake -Duse_wsio:bool=ON -Dskip_unittests:bool=ON .
make -j `nproc` streetlightd session-test azure-sas-token unit-test

