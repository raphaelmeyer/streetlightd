#!/bin/bash

export PATH=`pwd`:${PATH}

/home/root/source/doxygen/generate.sh
doxygen /home/root/source/Doxyfile

