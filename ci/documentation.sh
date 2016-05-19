#!/bin/bash

export PATH=`pwd`:${PATH}

doxygen/generate.sh
doxygen Doxyfile

