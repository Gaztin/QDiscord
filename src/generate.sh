#!/bin/bash

action="$1"


# Validate the premake executable
if [ ! -f "../bin/premake5" ]; then
	echo "Premake executable not found. Run 'init' to fetch one."
	read -p "Press enter to continue.."
	exit
fi


# Make sure action is valid
if [ "$action" == "" ]; then
	action="vs2015"
fi


# Generate project files
../bin/premake5 "--file=premake/all.lua" "$action"