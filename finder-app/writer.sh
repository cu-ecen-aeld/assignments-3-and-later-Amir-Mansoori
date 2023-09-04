#!/bin/bash
num=$#
writefile=$1
writestr=$2
if [ "${num}" -ne 2 ]
then
echo "Invalid number of arguments"
exit 1
fi
dirpath=$(dirname "${writefile}")
if [ ! -f "${writefile}" ]
then
mkdir -p "${dirpath}"
fi
touch "${writefile}"
echo "${writestr}" > "${writefile}"
if [ -f "${writefile}" ]
then
echo "Success! file has been created"
else
echo "Failed to create the file"
exit 1
fi

