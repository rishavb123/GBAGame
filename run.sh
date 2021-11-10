#!/bin/bash

# Recursively get all c files
cfiles=$(find . -type f -name \*.c) # get all the c files in the directory

# Preprocess the output string
ofiles="${cfiles//.c/.o}" # replace .c with .o
ofiles="${cfiles//.\//}" # get rid of all the ./
output="OFILES = ${ofiles//$'\n'/ }" # get rid of new lines and add OFILES
output="${output//\//\\\/}" # replace / with \/

echo $output

# put all required o files into Makefile
sed -i "17s/.*/$output/" Makefile # replace line 17 with $output

# sleep for 2 seconds
sleep 2

# actually run the gba program
make clean # clean previous runs
make med # run program
make clean # clean the run