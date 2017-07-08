#!/usr/bin/env bash
find images -name "*thumb*" | while read file; do
rm -Rf $file
done
