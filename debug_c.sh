#! /bin/bash
# compile the c file and enter the debug mode
# usage:
#		./debug_c.sh c_source_pathname

SourceName=$1

echo -e "(`date +"%Y/%m/%d %H:%M:%S"`) Begin to compile: $SourceName"

if [ ! -f $SourceName ]; then
	echo "No such file: \"$SourceName\"!"
	exit 1
fi

OutputFileName="`echo $SourceName | sed 's/.*\///g; s/\.[cC]$//g'`"

if [ "$OutputFileName" == "" ]; then
	echo "Output file name is empty!"
	exit 1
fi

gcc -ggdb3 -Wall $SourceName -o $OutputFileName

if [ $? -eq 0 ]; then
	CompileOk=1
else
	CompileOk=0
fi

echo -e "(`date +"%Y/%m/%d %H:%M:%S"`) Compile finish."

[ $CompileOk -eq 1 ] && gdb $OutputFileName

