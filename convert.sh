#!/bin/bash

INPUT_FILE=$1
OUTPUT_FILE=$2
MODE=$3

if [[ $# -ne 3 ]] # Ensure proper number of arguments
then
    echo "Incorrect number of arguments supplied. Proper syntax is ./convert.sh <input name> <output name> <mode>"
    echo "<input name>: Input file to specified operation."
    echo "<output name>: Output file to specified operation."
    echo "<mode>: Use 'var' to convert an ez80 Studio AppVar to assembly source, or 'asm' to convert assembly source to an ez80 Studio AppVar."
    exit 1
fi

if [[ ! -f $INPUT_FILE ]] # Ensure the specified file exists
then
    echo "The specified file does not exist. Please ensure that the file and path specified were correct and try again."
    exit 1
fi

if [[ $MODE == "var" ]] # Convert AppVar to assembly source file
then
    echo "Converting from AppVar..."

    convbin -j 8x -k bin -i $INPUT_FILE -o $OUTPUT_FILE

    echo "AppVar converted successfully."
    echo "Removing header..."

    sed -i 's/\xEF\x7A//g' $OUTPUT_FILE # Remove header

    echo "Header removed."

elif [[ $MODE == "asm" ]] # Convert assembly source file to AppVar 
then
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
    echo "Converting tabs..."

    sed -i 's/\t/  /g' temp_$INPUT_FILE

    echo "Tabs converted succesfully."
    echo "Converting to AppVar format..."

    convbin -j bin -k 8xv -i temp_$INPUT_FILE -o $OUTPUT_FILE.8xv -n $OUTPUT_FILE

    if [[ ! -f $OUTPUT_FILE.8xv ]] # Ensure the file got created
    then
        echo "The conversion failed. Please ensure convbin is installed on your system and try again."
        exit 1
    fi

    rm temp_$INPUT_FILE

else
    echo "Invalid mode. Use 'var' to convert an ez80 Studio AppVar to assembly source, or 'asm' to convert assembly source to an ez80 Studio AppVar."
    exit 1
fi

echo "Success!"
