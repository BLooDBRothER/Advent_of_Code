#!/bin/bash

if [ $# -eq 0 ]
then
    echo "Please enter the day no"
    exit 1
fi

export dayNo=$1

source .env

folderName="$YEAR/day$1"
fileName="day$1.cpp"
filePath="$folderName/$fileName"

templateFilePath="template/starter.txt"

if [[ -d "$folderName" ]]
then
    echo "$folderName directory does exists on your filesystem."
    exit 1
fi

echo "Creating Folder..."
mkdir -p $folderName

echo "Creating Necessary Files..."
touch $filePath $folderName/part1.h $folderName/part2.h

echo "Creating Starter Template..."
cat $templateFilePath | envsubst > $filePath

echo "Fetching Input..."
curl -H "Connection: close" --cookie "session=$AOC_SESSION_COOKIE" https://adventofcode.com/$YEAR/day/$1/input -o $folderName/input.txt
