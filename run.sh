#!/bin/sh

g++ -o test main.cpp -std=c++11 -Iinclude -lCGAL_Core -lCGAL -lboost_thread -lmpfr -lgmp
./test

