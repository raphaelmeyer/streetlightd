#!/bin/bash

cmake /home/root/source
make -j `nproc` streetlightd session-test azure-sas-token unit-test

