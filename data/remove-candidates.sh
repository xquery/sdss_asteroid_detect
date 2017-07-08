#!/usr/bin/env bash
find images -name "*.candidate.jpg" | while read file; do
rm -Rf $file
done
