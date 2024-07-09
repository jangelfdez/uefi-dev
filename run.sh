#!/bin/bash

# Exit immediately if any command exits with a non-zero status
set -e

make clean
make 
cd UEFI-GPT-image-creator
./write_gpt
./qemu.sh
