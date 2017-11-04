#!/usr/bin/env bash

search=${1}

find images -name "*308*.jpg" | while read file; do
echo "processing $file"
../cmake-build-debug/naive_detect $file
done
