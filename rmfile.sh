#! /bin/bash
# remove file *, *.in, *.out
# usage:
#		./rmfile.sh filename

filename=$1

count=0

if [ -e $filename ]; then
	rm -f -v $filename
	count=1
fi

if [ -e $filename".in" ]; then
	rm -f -v $filename".in"
	count=1
fi

if [ -e $filename".out" ]; then
	rm -f -v $filename".out"
	count=1
fi

if [ $count == 0 ]; then
	echo "No file was deleted."
fi

