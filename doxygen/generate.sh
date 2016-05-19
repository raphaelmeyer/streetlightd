#!/bin/bash

cd `dirname $0`

rm -f usage.dox
cat usage_part1.dox.fragment >> usage.dox
bash -c "streetlightd --help" >> usage.dox
cat usage_part2.dox.fragment >> usage.dox
bash -c "session-test --help" >> usage.dox
cat usage_part3.dox.fragment >> usage.dox
bash -c "azure-sas-token --help" >> usage.dox
cat usage_part4.dox.fragment >> usage.dox

