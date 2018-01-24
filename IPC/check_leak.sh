#!/bin/bash
if [ -z "$1" ]
then
	echo "Usage: $1 <binary_name>"
fi
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-result.txt ./${1}
