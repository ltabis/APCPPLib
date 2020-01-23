#!/bin/bash

cd build && cmake --build . -- -j 4 && cd ..
./tests/unit_tests
./test.sh
./a.out
