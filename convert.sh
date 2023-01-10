#!/bin/bash

INPUT_FILE=$1
OUTPUT_FILE=$2

if [[ $# -ne 2 ]] # Ensure proper number of arguments
then
    echo "Incorrect number of arguments supplied. Proper syntax is ./convert.sh <input name> <output name>"
    exit 1
fi

if [[ ! -f $INPUT_FILE ]] # Ensure the specified file exists
then
    echo "The specified file does not exist. Please ensure that the file and path specified were correct and try again."
    exit 1
fi

echo "Adding header..."

echo -n -e '\xEF\x7A' | cat - $INPUT_FILE > temp_$INPUT_FILE

if [[ ! -f temp_$INPUT_FILE ]] # Ensure the specified file exists
then
    echo "The header was not able to be added. Ensure you are in the directory with your input file and try again."
    exit 1
fi

echo "Header added succesfully."

echo "Converting newlines..."

sed -i 's/\r\n/\n/g' temp_$INPUT_FILE # Get rid of windows garbage (Hopefully nothing goes wrong here)

echo "Newlines converted succesfully."

echo "Converting to AppVar format..."

convbin -j bin -k 8xv -i temp_$INPUT_FILE -o $OUTPUT_FILE.8xv -n $OUTPUT_FILE

if [[ ! -f $OUTPUT_FILE.8xv ]] # Ensure the file got created
then
    echo "The conversion failed. Please try again"
    exit 1
fi

rm temp_$INPUT_FILE

echo "Success!"
