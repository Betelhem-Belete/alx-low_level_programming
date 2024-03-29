#!/bin/bash
gcc -c -FPIC *.c
gcc -shared -o liball.so *.o
