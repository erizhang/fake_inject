#!/bin/bash

cd external/cpputest/cpputest_build
autoreconf -i ..
../configure
echo "CONFIGURATION DONE. CppUTest Compiling now."
make

cd -

cd tests
make
cd -
