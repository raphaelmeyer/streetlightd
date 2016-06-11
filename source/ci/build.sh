#!/bin/bash

cmake /home/user/source
make -j `nproc` streetlightd session-test azure-sas-token unit-test

