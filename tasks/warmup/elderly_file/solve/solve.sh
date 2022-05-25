#!/bin/bash

python decoder.py file.enc
./ih2bin.sh file.enc.dec binary
strings binary | grep "Aero{"
