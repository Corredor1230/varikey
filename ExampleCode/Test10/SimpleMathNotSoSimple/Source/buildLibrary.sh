#!/bin/bash
for fullFileName in library/*.dsp; do
	file=$(basename $fullFileName)
	name=${file%%.*}
	echo "Building "$name
	faust -cn $name -ns faust -double $fullFileName -o $name.h
done
