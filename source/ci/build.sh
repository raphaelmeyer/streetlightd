#!/bin/bash

cmake .
make -j `nproc` streetlightd session-test azure-sas-token unit-test

