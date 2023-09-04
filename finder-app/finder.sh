#!/bin/bash
num=$#
filesdir=$1
searchstr=$2
if [ ${num} -ne 2 ]
then
   echo "Invaid number of arguments"
   exit 1
else
   if [ -d ${filesdir} ]
   then
      echo "${filesdir} is a directory"
   else
      exit 1
   fi
fi
numfiles=$(find ${filesdir} -type f | wc -l)
numlines=$(grep -r "/*${searchstr}/*" ${filesdir} | wc -l)
echo "The number of files are ${numfiles} and the number of matching lines are ${numlines}"
