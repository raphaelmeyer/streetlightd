#!/bin/bash

export PATH=`pwd`:${PATH}

/home/user/source/doxygen/generate.sh
doxygen /home/user/source/Doxyfile

