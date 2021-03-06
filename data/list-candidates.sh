#!/usr/bin/env bash
find images -name "*.candidate.jpg" | while read file; do
fname=`basename $file | cut -d'.' -f1`
v1=`echo ${fname:10} | cut -d'-' -f1 | sed 's/^0*//'`
v2=`echo ${fname:10} | cut -d'-' -f2`
v3=`echo ${fname:10} | cut -d'-' -f3 | sed 's/^0*//'`
echo "${v1} ${v2} ${v3}"

done
